#include "gateway_stats.h"

#include <stdint.h>

enum gateway_stats_status gateway_mean_i32(const int32_t *values,
                                           size_t count,
                                           int32_t *out_mean)
{
    int64_t sum = 0;

    if (out_mean == NULL || values == NULL) {
        return GATEWAY_STATS_INVALID_ARGUMENT;
    }
    if (count == 0U) {
        return GATEWAY_STATS_EMPTY;
    }

    for (size_t index = 0; index < count; ++index) {
        sum += values[index];
    }
    *out_mean = (int32_t)(sum / (int64_t)count);
    return GATEWAY_STATS_OK;
}
