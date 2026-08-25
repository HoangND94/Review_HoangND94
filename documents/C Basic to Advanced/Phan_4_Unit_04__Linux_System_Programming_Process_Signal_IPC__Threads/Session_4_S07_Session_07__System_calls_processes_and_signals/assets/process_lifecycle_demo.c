#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t interrupt_requested = 0;

static void on_interrupt(int signal_number) {
    (void)signal_number;
    interrupt_requested = 1;
}

static int count_open_fds(void) {
    DIR *directory = opendir("/proc/self/fd");
    if (directory == NULL) {
        return -1;
    }
    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            ++count;
        }
    }
    closedir(directory);
    return count;
}

static int set_close_on_exec(int fd) {
    int flags;
    do {
        flags = fcntl(fd, F_GETFD);
    } while (flags < 0 && errno == EINTR);
    if (flags < 0) {
        return -1;
    }
    int result;
    do {
        result = fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
    } while (result < 0 && errno == EINTR);
    return result;
}

static int read_bounded(int fd, char *buffer, size_t capacity, size_t *used) {
    *used = 0;
    while (*used < capacity - 1) {
        ssize_t amount = read(fd, buffer + *used, capacity - 1 - *used);
        if (amount > 0) {
            *used += (size_t)amount;
            continue;
        }
        if (amount == 0) {
            buffer[*used] = '\0';
            return 0;
        }
        if (errno == EINTR) {
            continue;
        }
        return -1;
    }
    buffer[*used] = '\0';
    errno = ENOBUFS;
    return -1;
}

static pid_t wait_owned_child(pid_t child_pid, int *status) {
    pid_t result;
    do {
        result = waitpid(child_pid, status, 0);
    } while (result < 0 && errno == EINTR);
    return result;
}

static int run_exit_case(void) {
    int baseline_fds = count_open_fds();
    int pipe_fds[2];
    if (baseline_fds < 0) {
        perror("count_open_fds");
        return EXIT_FAILURE;
    }
    if (pipe(pipe_fds) != 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    if (set_close_on_exec(pipe_fds[0]) != 0 ||
        set_close_on_exec(pipe_fds[1]) != 0) {
        perror("fcntl(FD_CLOEXEC)");
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return EXIT_FAILURE;
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return EXIT_FAILURE;
    }
    if (child_pid == 0) {
        close(pipe_fds[0]);
        if (dup2(pipe_fds[1], STDOUT_FILENO) < 0) {
            _exit(126);
        }
        close(pipe_fds[1]);
        char *const arguments[] = {
            (char *)"sh",
            (char *)"-c",
            (char *)"printf 'fixture-output\\n'; exit 7",
            NULL
        };
        execv("/bin/sh", arguments);
        _exit(127);
    }

    close(pipe_fds[1]);
    char output[128];
    size_t output_length = 0;
    bool read_ok = read_bounded(pipe_fds[0], output, sizeof(output),
                                &output_length) == 0;
    close(pipe_fds[0]);

    int status = 0;
    bool reaped = wait_owned_child(child_pid, &status) == child_pid;
    int final_fds = count_open_fds();
    int fd_delta = final_fds >= 0 ? final_fds - baseline_fds : -999;

    printf("child_output=%.*s", (int)output_length, output);
    printf("mode=exit exited=%d code=%d reaped=%d fd_delta=%d\n",
           reaped && WIFEXITED(status) ? 1 : 0,
           reaped && WIFEXITED(status) ? WEXITSTATUS(status) : -1,
           reaped ? 1 : 0,
           fd_delta);

    return read_ok && strcmp(output, "fixture-output\n") == 0 && reaped &&
                   WIFEXITED(status) && WEXITSTATUS(status) == 7 && fd_delta == 0
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}

static int run_interrupt_case(void) {
    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (child_pid == 0) {
        char *const arguments[] = {(char *)"sleep", (char *)"10", NULL};
        execv("/bin/sleep", arguments);
        _exit(127);
    }

    if (raise(SIGINT) != 0 || !interrupt_requested) {
        (void)kill(child_pid, SIGKILL);
        (void)wait_owned_child(child_pid, &(int){0});
        return EXIT_FAILURE;
    }
    if (kill(child_pid, SIGTERM) != 0) {
        (void)kill(child_pid, SIGKILL);
        (void)wait_owned_child(child_pid, &(int){0});
        return EXIT_FAILURE;
    }

    int status = 0;
    bool reaped = wait_owned_child(child_pid, &status) == child_pid;
    int signal_number = reaped && WIFSIGNALED(status) ? WTERMSIG(status) : -1;
    printf("mode=interrupt requested=%d signal=%d reaped=%d\n",
           interrupt_requested ? 1 : 0,
           signal_number,
           reaped ? 1 : 0);
    return reaped && WIFSIGNALED(status) && signal_number == SIGTERM
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}

int main(int argc, char **argv) {
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = on_interrupt;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGINT, &action, NULL) != 0) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    if (argc == 1) {
        return run_exit_case();
    }
    if (argc == 2 && strcmp(argv[1], "interrupt") == 0) {
        return run_interrupt_case();
    }
    fprintf(stderr, "usage: %s [interrupt]\n", argv[0]);
    return EXIT_FAILURE;
}
