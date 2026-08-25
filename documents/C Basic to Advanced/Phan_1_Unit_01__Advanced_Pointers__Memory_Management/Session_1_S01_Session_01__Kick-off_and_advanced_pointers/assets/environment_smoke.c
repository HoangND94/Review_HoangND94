#include <stdio.h>

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201710L
#error "This example requires C17 mode"
#endif

int main(void)
{
    puts("ENV_SMOKE PASS");
    return 0;
}
