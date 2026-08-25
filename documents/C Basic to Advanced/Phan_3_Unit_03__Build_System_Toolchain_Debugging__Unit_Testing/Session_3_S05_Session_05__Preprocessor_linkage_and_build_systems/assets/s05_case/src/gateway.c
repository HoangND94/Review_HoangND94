#include "gateway.h"

#include <limits.h>

static int32_t clamp_i64_to_i32(int64_t value)
{
    if (value > INT32_MAX) {
        return INT32_MAX;
    }
    if (value < INT32_MIN) {
        return INT32_MIN;
    }
    return (int32_t)value;
}

const char *gateway_version(void)
{
    return "5.0.0";
}

const char *gateway_event_name(enum gateway_event event)
{
    switch (event) {
#define X(name, value) case name: return #name;
#include "gateway_events.def"
#undef X
    default:
        return "GATEWAY_EVENT_UNKNOWN";
    }
}

int32_t gateway_apply_gain(int32_t sample, int32_t gain)
{
    return clamp_i64_to_i32((int64_t)sample * (int64_t)gain);
}
