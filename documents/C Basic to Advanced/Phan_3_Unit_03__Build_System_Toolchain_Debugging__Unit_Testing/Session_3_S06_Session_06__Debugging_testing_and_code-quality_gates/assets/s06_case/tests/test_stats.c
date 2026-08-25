#include "gateway_stats.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

#include <cmocka.h>

static void test_mean_normal(void **state)
{
    const int32_t values[] = {2, 4, 6, 8};
    int32_t mean = 0;
    (void)state;

    assert_int_equal(gateway_mean_i32(values, 4U, &mean), GATEWAY_STATS_OK);
    assert_int_equal(mean, 5);
}

static void test_mean_extremes_use_wide_sum(void **state)
{
    const int32_t values[] = {INT32_MAX, INT32_MAX};
    int32_t mean = 0;
    (void)state;

    assert_int_equal(gateway_mean_i32(values, 2U, &mean), GATEWAY_STATS_OK);
    assert_int_equal(mean, INT32_MAX);
}

static void test_mean_rejects_null(void **state)
{
    const int32_t values[] = {1};
    int32_t mean = 99;
    (void)state;

    assert_int_equal(gateway_mean_i32(NULL, 1U, &mean),
                     GATEWAY_STATS_INVALID_ARGUMENT);
    assert_int_equal(gateway_mean_i32(values, 1U, NULL),
                     GATEWAY_STATS_INVALID_ARGUMENT);
    assert_int_equal(mean, 99);
}

static void test_mean_rejects_empty(void **state)
{
    const int32_t values[] = {1};
    int32_t mean = 77;
    (void)state;

    assert_int_equal(gateway_mean_i32(values, 0U, &mean), GATEWAY_STATS_EMPTY);
    assert_int_equal(mean, 77);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_mean_normal),
        cmocka_unit_test(test_mean_extremes_use_wide_sum),
        cmocka_unit_test(test_mean_rejects_null),
        cmocka_unit_test(test_mean_rejects_empty)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
