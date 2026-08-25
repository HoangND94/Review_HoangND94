#define _GNU_SOURCE

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

enum {
    MAX_CONNECTIONS = 8,
    MAX_EVENTS = 16,
    INPUT_CAPACITY = 512,
    OUTPUT_CAPACITY = 1024,
    LOOP_LIMIT = 40
};

struct connection {
    int fd;
    char input[INPUT_CAPACITY];
    size_t input_length;
    char output[OUTPUT_CAPACITY];
    size_t output_length;
    size_t output_sent;
    bool peer_closed;
};

static volatile sig_atomic_t stop_requested = 0;

static void on_terminate(int signal_number) {
    (void)signal_number;
    stop_requested = 1;
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

static int send_all(int fd, const char *data, size_t length) {
    size_t sent = 0;
    while (sent < length) {
        ssize_t result = send(fd, data + sent, length - sent, MSG_NOSIGNAL);
        if (result > 0) {
            sent += (size_t)result;
            continue;
        }
        if (result < 0 && errno == EINTR) {
            continue;
        }
        return -1;
    }
    return 0;
}

static int run_client(struct sockaddr_in address, int listener_fd, int epoll_fd) {
    close(listener_fd);
    close(epoll_fd);

    int fd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        return 10;
    }
    struct timeval timeout = {.tv_sec = 3, .tv_usec = 0};
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0 ||
        connect(fd, (const struct sockaddr *)&address, sizeof(address)) != 0) {
        close(fd);
        return 11;
    }

    if (send_all(fd, "PI", 2) != 0) {
        close(fd);
        return 12;
    }
    const struct timespec pause_time = {.tv_sec = 0, .tv_nsec = 20000000L};
    (void)nanosleep(&pause_time, NULL);
    if (send_all(fd, "NG\nECHO xin-chao\n", 19) != 0 || shutdown(fd, SHUT_WR) != 0) {
        close(fd);
        return 13;
    }

    char response[64];
    size_t used = 0;
    unsigned lines = 0;
    while (used < sizeof(response) - 1 && lines < 2) {
        ssize_t received = recv(fd, response + used, sizeof(response) - 1 - used, 0);
        if (received > 0) {
            for (ssize_t index = 0; index < received; ++index) {
                if (response[used + (size_t)index] == '\n') {
                    ++lines;
                }
            }
            used += (size_t)received;
            continue;
        }
        if (received < 0 && errno == EINTR) {
            continue;
        }
        close(fd);
        return 14;
    }
    response[used] = '\0';
    close(fd);
    return strcmp(response, "PONG\nxin-chao\n") == 0 ? 0 : 15;
}

static struct connection *find_connection(struct connection *connections, int fd) {
    for (size_t index = 0; index < MAX_CONNECTIONS; ++index) {
        if (connections[index].fd == fd) {
            return &connections[index];
        }
    }
    return NULL;
}

static struct connection *add_connection(struct connection *connections, int fd) {
    for (size_t index = 0; index < MAX_CONNECTIONS; ++index) {
        if (connections[index].fd == -1) {
            connections[index] = (struct connection){.fd = fd};
            return &connections[index];
        }
    }
    return NULL;
}

static size_t active_connections(const struct connection *connections) {
    size_t count = 0;
    for (size_t index = 0; index < MAX_CONNECTIONS; ++index) {
        if (connections[index].fd >= 0) {
            ++count;
        }
    }
    return count;
}

static void close_connection(int epoll_fd, struct connection *connection) {
    if (connection->fd >= 0) {
        (void)epoll_ctl(epoll_fd, EPOLL_CTL_DEL, connection->fd, NULL);
        close(connection->fd);
        connection->fd = -1;
    }
}

static int append_output(struct connection *connection,
                         const char *data,
                         size_t length) {
    if (length > OUTPUT_CAPACITY - connection->output_length) {
        return -1;
    }
    memcpy(connection->output + connection->output_length, data, length);
    connection->output_length += length;
    return 0;
}

static int process_frames(struct connection *connection,
                          unsigned *frames,
                          unsigned *responses) {
    for (;;) {
        char *newline = memchr(connection->input, '\n', connection->input_length);
        if (newline == NULL) {
            return 0;
        }
        size_t line_length = (size_t)(newline - connection->input);
        int result;
        if (line_length == 4 && memcmp(connection->input, "PING", 4) == 0) {
            result = append_output(connection, "PONG\n", 5);
        } else if (line_length >= 5 && memcmp(connection->input, "ECHO ", 5) == 0) {
            result = append_output(connection, connection->input + 5, line_length - 5);
            if (result == 0) {
                result = append_output(connection, "\n", 1);
            }
        } else {
            result = append_output(connection, "ERR\n", 4);
        }
        if (result != 0) {
            return -1;
        }
        ++*frames;
        ++*responses;

        size_t consumed = line_length + 1;
        size_t remaining = connection->input_length - consumed;
        memmove(connection->input, connection->input + consumed, remaining);
        connection->input_length = remaining;
    }
}

static int read_available(struct connection *connection,
                          unsigned *frames,
                          unsigned *responses) {
    char chunk[128];
    for (;;) {
        ssize_t received = recv(connection->fd, chunk, sizeof(chunk), 0);
        if (received > 0) {
            size_t amount = (size_t)received;
            if (amount > INPUT_CAPACITY - connection->input_length) {
                return -1;
            }
            memcpy(connection->input + connection->input_length, chunk, amount);
            connection->input_length += amount;
            if (process_frames(connection, frames, responses) != 0) {
                return -1;
            }
            continue;
        }
        if (received == 0) {
            connection->peer_closed = true;
            return 0;
        }
        if (errno == EINTR) {
            continue;
        }
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        }
        return -1;
    }
}

static int flush_available(struct connection *connection) {
    while (connection->output_sent < connection->output_length) {
        ssize_t sent = send(connection->fd,
                            connection->output + connection->output_sent,
                            connection->output_length - connection->output_sent,
                            MSG_NOSIGNAL);
        if (sent > 0) {
            connection->output_sent += (size_t)sent;
            continue;
        }
        if (sent < 0 && errno == EINTR) {
            continue;
        }
        if (sent < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return 0;
        }
        return -1;
    }
    connection->output_length = 0;
    connection->output_sent = 0;
    return 0;
}

static int update_interest(int epoll_fd, const struct connection *connection) {
    struct epoll_event event = {
        .events = EPOLLIN | EPOLLRDHUP |
                  (connection->output_length > connection->output_sent ? EPOLLOUT : 0U),
        .data.fd = connection->fd
    };
    return epoll_ctl(epoll_fd, EPOLL_CTL_MOD, connection->fd, &event);
}

int main(void) {
    int baseline_fds = count_open_fds();
    if (baseline_fds < 0) {
        perror("count_open_fds");
        return EXIT_FAILURE;
    }

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = on_terminate;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGTERM, &action, NULL) != 0) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    int listener_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (listener_fd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(0);
    if (bind(listener_fd, (const struct sockaddr *)&address, sizeof(address)) != 0 ||
        listen(listener_fd, 8) != 0) {
        perror("bind/listen");
        close(listener_fd);
        return EXIT_FAILURE;
    }
    socklen_t address_length = sizeof(address);
    if (getsockname(listener_fd, (struct sockaddr *)&address, &address_length) != 0) {
        perror("getsockname");
        close(listener_fd);
        return EXIT_FAILURE;
    }

    int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        close(listener_fd);
        return EXIT_FAILURE;
    }
    struct epoll_event listener_event = {.events = EPOLLIN, .data.fd = listener_fd};
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener_fd, &listener_event) != 0) {
        perror("epoll_ctl(listener)");
        close(epoll_fd);
        close(listener_fd);
        return EXIT_FAILURE;
    }

    pid_t client_pid = fork();
    if (client_pid < 0) {
        perror("fork");
        close(epoll_fd);
        close(listener_fd);
        return EXIT_FAILURE;
    }
    if (client_pid == 0) {
        _exit(run_client(address, listener_fd, epoll_fd));
    }

    struct connection connections[MAX_CONNECTIONS];
    for (size_t index = 0; index < MAX_CONNECTIONS; ++index) {
        connections[index].fd = -1;
    }

    unsigned frames = 0;
    unsigned responses = 0;
    int child_status = -1;
    bool child_done = false;
    bool server_error = false;

    for (unsigned iteration = 0; iteration < LOOP_LIMIT && !stop_requested; ++iteration) {
        struct epoll_event events[MAX_EVENTS];
        int ready = epoll_wait(epoll_fd, events, MAX_EVENTS, 250);
        if (ready < 0) {
            if (errno == EINTR) {
                continue;
            }
            server_error = true;
            break;
        }
        for (int event_index = 0; event_index < ready; ++event_index) {
            int fd = events[event_index].data.fd;
            uint32_t flags = events[event_index].events;
            if (fd == listener_fd) {
                for (;;) {
                    int client_fd = accept4(listener_fd, NULL, NULL,
                                            SOCK_NONBLOCK | SOCK_CLOEXEC);
                    if (client_fd >= 0) {
                        struct connection *connection = add_connection(connections, client_fd);
                        struct epoll_event event = {
                            .events = EPOLLIN | EPOLLRDHUP,
                            .data.fd = client_fd
                        };
                        if (connection == NULL ||
                            epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) != 0) {
                            close(client_fd);
                            if (connection != NULL) {
                                connection->fd = -1;
                            }
                            server_error = true;
                        }
                        continue;
                    }
                    if (errno == EINTR) {
                        continue;
                    }
                    if (errno != EAGAIN && errno != EWOULDBLOCK) {
                        server_error = true;
                    }
                    break;
                }
                continue;
            }

            struct connection *connection = find_connection(connections, fd);
            if (connection == NULL) {
                server_error = true;
                continue;
            }
            if ((flags & EPOLLIN) != 0U &&
                read_available(connection, &frames, &responses) != 0) {
                connection->peer_closed = true;
                server_error = true;
            }
            if ((flags & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) != 0U) {
                connection->peer_closed = true;
            }
            if (connection->output_length > connection->output_sent &&
                flush_available(connection) != 0) {
                connection->peer_closed = true;
                server_error = true;
            }
            if (connection->peer_closed &&
                connection->output_length == connection->output_sent) {
                close_connection(epoll_fd, connection);
            } else if (update_interest(epoll_fd, connection) != 0) {
                close_connection(epoll_fd, connection);
                server_error = true;
            }
        }

        if (!child_done) {
            pid_t waited = waitpid(client_pid, &child_status, WNOHANG);
            if (waited == client_pid) {
                child_done = true;
            } else if (waited < 0 && errno != EINTR) {
                server_error = true;
                break;
            }
        }
        if (child_done && active_connections(connections) == 0 && frames == 2) {
            break;
        }
    }

    if (!child_done) {
        int signal_number = stop_requested ? SIGTERM : SIGKILL;
        (void)kill(client_pid, signal_number);
        while (waitpid(client_pid, &child_status, 0) < 0 && errno == EINTR) {
        }
        child_done = true;
    }
    for (size_t index = 0; index < MAX_CONNECTIONS; ++index) {
        close_connection(epoll_fd, &connections[index]);
    }
    close(listener_fd);
    close(epoll_fd);

    int final_fds = count_open_fds();
    int child_code = child_done && WIFEXITED(child_status) ? WEXITSTATUS(child_status) : -1;
    int fd_delta = final_fds >= 0 ? final_fds - baseline_fds : -999;
    printf("frames=%u responses=%u child_exit=%d fd_delta=%d\n",
           frames, responses, child_code, fd_delta);

    return !server_error && frames == 2 && responses == 2 && child_code == 0 &&
                   fd_delta == 0
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}
