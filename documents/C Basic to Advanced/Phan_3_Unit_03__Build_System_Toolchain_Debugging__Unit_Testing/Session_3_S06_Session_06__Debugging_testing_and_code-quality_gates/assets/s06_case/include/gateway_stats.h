#ifndef S06_GATEWAY_STATS_H
#define S06_GATEWAY_STATS_H

#include <stddef.h>
#include <stdint.h>

enum gateway_stats_status {
    GATEWAY_STATS_OK = 0,
    GATEWAY_STATS_INVALID_ARGUMENT = 1,
    GATEWAY_STATS_EMPTY = 2
};

enum gateway_stats_status gateway_mean_i32(const int32_t *values,
                                           size_t count,
                                           int32_t *out_mean);

#endif
