#ifndef S05_GATEWAY_H
#define S05_GATEWAY_H

#include <stdint.h>

#if defined(GATEWAY_BUILD_SHARED) && (defined(__GNUC__) || defined(__clang__))
#define GATEWAY_API __attribute__((visibility("default")))
#else
#define GATEWAY_API
#endif

enum gateway_event {
#define X(name, value) name = value,
#include "gateway_events.def"
#undef X
};

GATEWAY_API const char *gateway_version(void);
GATEWAY_API const char *gateway_event_name(enum gateway_event event);
GATEWAY_API int32_t gateway_apply_gain(int32_t sample, int32_t gain);

#endif
