#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DISPATCH_OK = 0,
    DISPATCH_UNKNOWN,
    DISPATCH_BAD_ARGUMENT
} dispatch_status;

typedef dispatch_status (*command_fn)(const char *argument, void *context);

typedef struct {
    const char *name;
    command_fn callback;
    void *context;
} command_entry;

typedef struct {
    int calls;
    int last_value;
} counter_context;

static dispatch_status set_handler(const char *argument, void *context)
{
    counter_context *counter = context;
    char *end = NULL;
    long value;

    if (argument == NULL || counter == NULL) {
        return DISPATCH_BAD_ARGUMENT;
    }
    errno = 0;
    value = strtol(argument, &end, 10);
    if (errno == ERANGE || end == argument || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return DISPATCH_BAD_ARGUMENT;
    }
    counter->calls += 1;
    counter->last_value = (int)value;
    return DISPATCH_OK;
}

static dispatch_status dispatch(const command_entry *entries,
                                size_t count,
                                const char *name,
                                const char *argument)
{
    size_t i;

    if ((entries == NULL && count != 0U) || name == NULL) {
        return DISPATCH_BAD_ARGUMENT;
    }
    for (i = 0U; i < count; ++i) {
        if (entries[i].name != NULL && strcmp(entries[i].name, name) == 0) {
            if (entries[i].callback == NULL) {
                return DISPATCH_BAD_ARGUMENT;
            }
            return entries[i].callback(argument, entries[i].context);
        }
    }
    return DISPATCH_UNKNOWN;
}

static int compare_int(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;
    return (a > b) - (a < b);
}

static int find_int(const int *values, size_t count, int key, const int **out)
{
    const int *found;

    if (out == NULL || (values == NULL && count != 0U)) {
        return 0;
    }
    *out = NULL;
    found = bsearch(&key, values, count, sizeof values[0], compare_int);
    if (found == NULL) {
        return 0;
    }
    *out = found;
    return 1;
}

static int swap_elements(void *base, size_t count, size_t element_size,
                         size_t first, size_t second)
{
    unsigned char *bytes = base;
    size_t i;

    if (base == NULL || element_size == 0U || first >= count || second >= count) {
        return 0;
    }
    for (i = 0U; i < element_size; ++i) {
        unsigned char tmp = bytes[first * element_size + i];
        bytes[first * element_size + i] = bytes[second * element_size + i];
        bytes[second * element_size + i] = tmp;
    }
    return 1;
}

int main(void)
{
    counter_context counter = {0, 0};
    command_entry registry[] = {
        {"set", set_handler, &counter},
        {"disabled", NULL, &counter}
    };
    int values[] = {INT_MAX, 4, INT_MIN, 4, 0};
    const int expected[] = {INT_MIN, 0, 4, 4, INT_MAX};
    const int *found = NULL;
    size_t count = sizeof values / sizeof values[0];

    assert(dispatch(registry, 2U, "set", "17") == DISPATCH_OK);
    assert(counter.calls == 1 && counter.last_value == 17);
    assert(dispatch(registry, 2U, "missing", "0") == DISPATCH_UNKNOWN);
    assert(dispatch(registry, 2U, "disabled", "0") == DISPATCH_BAD_ARGUMENT);

    qsort(values, count, sizeof values[0], compare_int);
    assert(memcmp(values, expected, sizeof values) == 0);
    assert(find_int(values, count, 4, &found) == 1 && found != NULL && *found == 4);
    assert(find_int(values, count, 99, &found) == 0 && found == NULL);
    assert(swap_elements(values, count, sizeof values[0], 0U, count - 1U) == 1);
    assert(values[0] == INT_MAX && values[count - 1U] == INT_MIN);
    assert(swap_elements(values, count, sizeof values[0], count, 0U) == 0);

    puts("S01 DISPATCHER PASS");
    return 0;
}
