#include "gateway.h"

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    assert(strcmp(gateway_version(), "5.0.0") == 0);
    assert(strcmp(gateway_event_name(GATEWAY_EVENT_INFO),
                  "GATEWAY_EVENT_INFO") == 0);
    assert(strcmp(gateway_event_name((enum gateway_event)99),
                  "GATEWAY_EVENT_UNKNOWN") == 0);
    assert(gateway_apply_gain(4, 3) == 12);
    assert(gateway_apply_gain(INT32_MAX, 2) == INT32_MAX);
    assert(gateway_apply_gain(INT32_MIN, 2) == INT32_MIN);
    return 0;
}
