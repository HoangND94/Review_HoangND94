#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { SIDE = 256, DEFAULT_REPETITIONS = 200, MAX_REPETITIONS = 10000 };

static uint32_t matrix[SIDE][SIDE];

static void initialise_matrix(void) {
    for (size_t row = 0; row < SIDE; ++row) {
        for (size_t column = 0; column < SIDE; ++column) {
            matrix[row][column] = (uint32_t)((row * 131U + column * 17U) & 0xffU);
        }
    }
}

static uint64_t scan_rows(unsigned repetitions) {
    uint64_t checksum = 0;
    for (unsigned repeat = 0; repeat < repetitions; ++repeat) {
        for (size_t row = 0; row < SIDE; ++row) {
            for (size_t column = 0; column < SIDE; ++column) {
                checksum += matrix[row][column];
            }
        }
    }
    return checksum;
}

static uint64_t scan_columns(unsigned repetitions) {
    uint64_t checksum = 0;
    for (unsigned repeat = 0; repeat < repetitions; ++repeat) {
        for (size_t column = 0; column < SIDE; ++column) {
            for (size_t row = 0; row < SIDE; ++row) {
                checksum += matrix[row][column];
            }
        }
    }
    return checksum;
}

static int parse_repetitions(const char *text, unsigned *result) {
    char *end = NULL;
    errno = 0;
    unsigned long value = strtoul(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || value == 0 ||
        value > MAX_REPETITIONS) {
        return -1;
    }
    *result = (unsigned)value;
    return 0;
}

static uint64_t elapsed_ns(const struct timespec *start,
                           const struct timespec *finish) {
    uint64_t seconds = (uint64_t)(finish->tv_sec - start->tv_sec);
    long nanoseconds = finish->tv_nsec - start->tv_nsec;
    if (nanoseconds < 0) {
        --seconds;
        nanoseconds += 1000000000L;
    }
    return seconds * UINT64_C(1000000000) + (uint64_t)nanoseconds;
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4 ||
        (strcmp(argv[1], "row") != 0 && strcmp(argv[1], "column") != 0)) {
        fprintf(stderr, "usage: %s row|column [repetitions] [payload]\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned repetitions = DEFAULT_REPETITIONS;
    if (argc >= 3 && parse_repetitions(argv[2], &repetitions) != 0) {
        fprintf(stderr, "invalid repetitions: expected 1..%d\n", MAX_REPETITIONS);
        return EXIT_FAILURE;
    }

    const char *payload = argc == 4 ? argv[3] : "%n%s%x";
    initialise_matrix();

    struct timespec start;
    struct timespec finish;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        perror("clock_gettime(start)");
        return EXIT_FAILURE;
    }

    uint64_t checksum = strcmp(argv[1], "row") == 0
                            ? scan_rows(repetitions)
                            : scan_columns(repetitions);

    if (clock_gettime(CLOCK_MONOTONIC, &finish) != 0) {
        perror("clock_gettime(finish)");
        return EXIT_FAILURE;
    }

    printf("mode=%s repetitions=%u checksum=%" PRIu64 " elapsed_ns=%" PRIu64 "\n",
           argv[1], repetitions, checksum, elapsed_ns(&start, &finish));
    printf("payload=%s\n", payload);
    return EXIT_SUCCESS;
}
