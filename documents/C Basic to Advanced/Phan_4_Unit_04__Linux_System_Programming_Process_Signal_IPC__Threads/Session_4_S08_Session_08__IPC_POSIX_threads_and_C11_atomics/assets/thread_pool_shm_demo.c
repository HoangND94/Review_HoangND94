#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

enum { WORKER_COUNT = 2, TASK_COUNT = 8, QUEUE_CAPACITY = 3 };
enum { RESULT_MAGIC = 0x41445643U, RESULT_VERSION = 1U };

struct task {
    unsigned id;
    unsigned value;
};

struct result_channel {
    uint32_t magic;
    uint32_t version;
    uint32_t capacity;
    uint32_t reserved;
    uint64_t results[TASK_COUNT];
    atomic_uint processed;
};

struct task_queue {
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    struct task items[QUEUE_CAPACITY];
    size_t head;
    size_t tail;
    size_t count;
    bool stopping;
};

struct worker_context {
    struct task_queue *queue;
    struct result_channel *channel;
    atomic_int *worker_error;
};

static int report_pthread_error(int result, const char *operation) {
    if (result != 0) {
        fprintf(stderr, "%s: %s\n", operation, strerror(result));
        return -1;
    }
    return 0;
}

static int queue_initialise(struct task_queue *queue) {
    memset(queue, 0, sizeof(*queue));
    int result = pthread_mutex_init(&queue->mutex, NULL);
    if (report_pthread_error(result, "pthread_mutex_init") != 0) {
        return -1;
    }
    result = pthread_cond_init(&queue->not_empty, NULL);
    if (report_pthread_error(result, "pthread_cond_init(not_empty)") != 0) {
        (void)pthread_mutex_destroy(&queue->mutex);
        return -1;
    }
    result = pthread_cond_init(&queue->not_full, NULL);
    if (report_pthread_error(result, "pthread_cond_init(not_full)") != 0) {
        (void)pthread_cond_destroy(&queue->not_empty);
        (void)pthread_mutex_destroy(&queue->mutex);
        return -1;
    }
    return 0;
}

static int queue_submit(struct task_queue *queue, struct task task) {
    int result = pthread_mutex_lock(&queue->mutex);
    if (report_pthread_error(result, "pthread_mutex_lock(submit)") != 0) {
        return -1;
    }
    while (queue->count == QUEUE_CAPACITY && !queue->stopping) {
        result = pthread_cond_wait(&queue->not_full, &queue->mutex);
        if (report_pthread_error(result, "pthread_cond_wait(not_full)") != 0) {
            (void)pthread_mutex_unlock(&queue->mutex);
            return -1;
        }
    }
    if (queue->stopping) {
        (void)pthread_mutex_unlock(&queue->mutex);
        return -1;
    }
    queue->items[queue->tail] = task;
    queue->tail = (queue->tail + 1U) % QUEUE_CAPACITY;
    ++queue->count;
    result = pthread_cond_signal(&queue->not_empty);
    int unlock_result = pthread_mutex_unlock(&queue->mutex);
    return report_pthread_error(result, "pthread_cond_signal(not_empty)") == 0 &&
                   report_pthread_error(unlock_result,
                                        "pthread_mutex_unlock(submit)") == 0
               ? 0
               : -1;
}

static int queue_request_stop(struct task_queue *queue) {
    int result = pthread_mutex_lock(&queue->mutex);
    if (report_pthread_error(result, "pthread_mutex_lock(stop)") != 0) {
        return -1;
    }
    queue->stopping = true;
    result = pthread_cond_broadcast(&queue->not_empty);
    int unlock_result = pthread_mutex_unlock(&queue->mutex);
    return report_pthread_error(result, "pthread_cond_broadcast") == 0 &&
                   report_pthread_error(unlock_result,
                                        "pthread_mutex_unlock(stop)") == 0
               ? 0
               : -1;
}

static void record_worker_error(struct worker_context *context, int result,
                                const char *operation) {
    (void)report_pthread_error(result, operation);
    atomic_store_explicit(context->worker_error, 1, memory_order_relaxed);
}

static void *worker_main(void *argument) {
    struct worker_context *context = argument;
    struct task_queue *queue = context->queue;

    for (;;) {
        int result = pthread_mutex_lock(&queue->mutex);
        if (result != 0) {
            record_worker_error(context, result, "pthread_mutex_lock(worker)");
            return NULL;
        }
        while (queue->count == 0 && !queue->stopping) {
            result = pthread_cond_wait(&queue->not_empty, &queue->mutex);
            if (result != 0) {
                record_worker_error(context, result,
                                    "pthread_cond_wait(not_empty)");
                (void)pthread_mutex_unlock(&queue->mutex);
                return NULL;
            }
        }
        if (queue->count == 0 && queue->stopping) {
            result = pthread_mutex_unlock(&queue->mutex);
            if (result != 0) {
                record_worker_error(context, result,
                                    "pthread_mutex_unlock(worker-stop)");
            }
            return NULL;
        }

        struct task task = queue->items[queue->head];
        queue->head = (queue->head + 1U) % QUEUE_CAPACITY;
        --queue->count;
        result = pthread_cond_signal(&queue->not_full);
        if (result != 0) {
            record_worker_error(context, result,
                                "pthread_cond_signal(not_full)");
        }
        result = pthread_mutex_unlock(&queue->mutex);
        if (result != 0) {
            record_worker_error(context, result,
                                "pthread_mutex_unlock(worker)");
            return NULL;
        }

        context->channel->results[task.id] =
            (uint64_t)task.value * (uint64_t)task.value;
        (void)atomic_fetch_add_explicit(&context->channel->processed, 1U,
                                        memory_order_relaxed);
    }
}

static int queue_destroy(struct task_queue *queue) {
    int first = pthread_cond_destroy(&queue->not_full);
    int second = pthread_cond_destroy(&queue->not_empty);
    int third = pthread_mutex_destroy(&queue->mutex);
    return report_pthread_error(first, "pthread_cond_destroy(not_full)") == 0 &&
                   report_pthread_error(second,
                                        "pthread_cond_destroy(not_empty)") == 0 &&
                   report_pthread_error(third, "pthread_mutex_destroy") == 0
               ? 0
               : -1;
}

int main(void) {
    char shared_name[64];
    int name_length = snprintf(shared_name, sizeof(shared_name),
                               "/advc_s08_%ld", (long)getpid());
    if (name_length < 0 || (size_t)name_length >= sizeof(shared_name)) {
        fprintf(stderr, "shared-memory name too long\n");
        return EXIT_FAILURE;
    }

    int shared_fd = shm_open(shared_name,
                             O_CREAT | O_EXCL | O_RDWR | O_CLOEXEC, 0600);
    if (shared_fd < 0) {
        perror("shm_open");
        return EXIT_FAILURE;
    }
    if (ftruncate(shared_fd, (off_t)sizeof(struct result_channel)) != 0) {
        perror("ftruncate");
        close(shared_fd);
        (void)shm_unlink(shared_name);
        return EXIT_FAILURE;
    }
    struct result_channel *channel = mmap(NULL, sizeof(*channel),
                                          PROT_READ | PROT_WRITE, MAP_SHARED,
                                          shared_fd, 0);
    if (channel == MAP_FAILED) {
        perror("mmap");
        close(shared_fd);
        (void)shm_unlink(shared_name);
        return EXIT_FAILURE;
    }
    if (shm_unlink(shared_name) != 0) {
        perror("shm_unlink");
        munmap(channel, sizeof(*channel));
        close(shared_fd);
        return EXIT_FAILURE;
    }

    memset(channel, 0, sizeof(*channel));
    channel->magic = RESULT_MAGIC;
    channel->version = RESULT_VERSION;
    channel->capacity = TASK_COUNT;
    atomic_init(&channel->processed, 0U);

    struct task_queue queue;
    if (queue_initialise(&queue) != 0) {
        munmap(channel, sizeof(*channel));
        close(shared_fd);
        return EXIT_FAILURE;
    }
    atomic_int worker_error;
    atomic_init(&worker_error, 0);
    struct worker_context context = {
        .queue = &queue,
        .channel = channel,
        .worker_error = &worker_error
    };

    pthread_t workers[WORKER_COUNT];
    size_t created = 0;
    for (; created < WORKER_COUNT; ++created) {
        int result = pthread_create(&workers[created], NULL, worker_main, &context);
        if (report_pthread_error(result, "pthread_create") != 0) {
            break;
        }
    }

    bool submit_ok = created == WORKER_COUNT;
    for (unsigned id = 0; submit_ok && id < TASK_COUNT; ++id) {
        struct task task = {.id = id, .value = id + 1U};
        if (queue_submit(&queue, task) != 0) {
            submit_ok = false;
        }
    }
    bool stop_ok = queue_request_stop(&queue) == 0;

    bool join_ok = true;
    for (size_t index = 0; index < created; ++index) {
        int result = pthread_join(workers[index], NULL);
        if (report_pthread_error(result, "pthread_join") != 0) {
            join_ok = false;
        }
    }

    unsigned processed = atomic_load_explicit(&channel->processed,
                                               memory_order_relaxed);
    uint64_t checksum = 0;
    bool results_ok = channel->magic == RESULT_MAGIC &&
                      channel->version == RESULT_VERSION &&
                      channel->capacity == TASK_COUNT;
    for (unsigned id = 0; id < TASK_COUNT; ++id) {
        uint64_t expected = (uint64_t)(id + 1U) * (uint64_t)(id + 1U);
        checksum += channel->results[id];
        if (channel->results[id] != expected) {
            results_ok = false;
        }
    }

    bool destroy_ok = queue_destroy(&queue) == 0;
    bool unmap_ok = munmap(channel, sizeof(*channel)) == 0;
    bool close_ok = close(shared_fd) == 0;
    errno = 0;
    int stale_fd = shm_open(shared_name, O_RDWR | O_CLOEXEC, 0);
    bool cleanup_ok = stale_fd < 0 && errno == ENOENT;
    if (stale_fd >= 0) {
        close(stale_fd);
    }

    printf("submitted=%d processed=%u checksum=%llu cleanup=%s\n",
           submit_ok ? TASK_COUNT : 0,
           processed,
           (unsigned long long)checksum,
           cleanup_ok ? "ok" : "stale");

    return submit_ok && stop_ok && join_ok &&
                   atomic_load_explicit(&worker_error, memory_order_relaxed) == 0 &&
                   processed == TASK_COUNT && checksum == UINT64_C(204) &&
                   results_ok && destroy_ok && unmap_ok && close_ok && cleanup_ok
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}
