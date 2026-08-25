#include "gateway.h"

#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    const int32_t result = gateway_apply_gain(4, 3);
    printf("gateway %s\n", gateway_version());
    printf("event=%s result=%" PRId32 "\n",
           gateway_event_name(GATEWAY_EVENT_WARN), result);
    return result == 12 ? 0 : 1;
}
