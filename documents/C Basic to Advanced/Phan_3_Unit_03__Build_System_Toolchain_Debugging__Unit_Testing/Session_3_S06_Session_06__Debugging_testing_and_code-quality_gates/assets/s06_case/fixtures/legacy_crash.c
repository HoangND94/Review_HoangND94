#include <stdint.h>
#include <stddef.h>

static int32_t legacy_first(const int32_t *values)
{
    return values[0];
}

int main(int argc, char **argv)
{
    static const int32_t fallback[] = {7, 11};
    const int32_t *values = NULL;

    (void)argv;
    if (argc > 1) {
        values = fallback;
    }
    return legacy_first(values) == 7 ? 0 : 1;
}
