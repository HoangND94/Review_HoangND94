#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct byte_vector {
    unsigned char *data;
    size_t len;
    size_t cap;
    size_t elem_size;
};

static bool fail_next_allocation;

static void *case_realloc(void *old_data, size_t bytes)
{
    if (fail_next_allocation) {
        fail_next_allocation = false;
        return NULL;
    }
    return realloc(old_data, bytes);
}

static bool size_mul(size_t left, size_t right, size_t *result)
{
    if (result == NULL || (right != 0U && left > SIZE_MAX / right)) {
        return false;
    }
    *result = left * right;
    return true;
}

static bool vector_init(struct byte_vector *vector, size_t elem_size)
{
    if (vector == NULL || elem_size == 0U) {
        return false;
    }
    *vector = (struct byte_vector){.elem_size = elem_size};
    return true;
}

static bool vector_reserve(struct byte_vector *vector, size_t wanted)
{
    size_t new_cap;
    size_t bytes;
    void *new_data;

    if (vector == NULL || wanted <= vector->cap) {
        return vector != NULL;
    }
    new_cap = vector->cap == 0U ? 4U : vector->cap;
    while (new_cap < wanted) {
        if (new_cap > SIZE_MAX / 2U) {
            return false;
        }
        new_cap *= 2U;
    }
    if (!size_mul(new_cap, vector->elem_size, &bytes)) {
        return false;
    }
    new_data = case_realloc(vector->data, bytes);
    if (new_data == NULL) {
        return false;
    }
    vector->data = new_data;
    vector->cap = new_cap;
    return true;
}

static bool vector_push(struct byte_vector *vector, const void *element)
{
    size_t offset;

    if (vector == NULL || element == NULL || vector->len == SIZE_MAX ||
        !vector_reserve(vector, vector->len + 1U) ||
        !size_mul(vector->len, vector->elem_size, &offset)) {
        return false;
    }
    memcpy(vector->data + offset, element, vector->elem_size);
    ++vector->len;
    return true;
}

static const void *vector_at(const struct byte_vector *vector, size_t index)
{
    if (vector == NULL || index >= vector->len) {
        return NULL;
    }
    return vector->data + (index * vector->elem_size);
}

static void vector_destroy(struct byte_vector *vector)
{
    if (vector != NULL) {
        free(vector->data);
        *vector = (struct byte_vector){0};
    }
}

struct list_node {
    struct list_node *prev;
    struct list_node *next;
    bool linked;
};

struct record {
    int id;
    struct list_node active_link;
};

#define CONTAINER_OF(member_pointer, type, member) \
    ((type *)((unsigned char *)(member_pointer) - offsetof(type, member)))

#define CONTAINER_OF_CONST(member_pointer, type, member) \
    ((const type *)((const unsigned char *)(member_pointer) - \
                    offsetof(type, member)))

static void list_head_init(struct list_node *head)
{
    head->prev = head;
    head->next = head;
    head->linked = true;
}

static void list_node_init(struct list_node *node)
{
    node->prev = NULL;
    node->next = NULL;
    node->linked = false;
}

static bool list_insert_tail(struct list_node *head, struct list_node *node)
{
    if (head == NULL || node == NULL || node->linked) {
        return false;
    }
    node->prev = head->prev;
    node->next = head;
    head->prev->next = node;
    head->prev = node;
    node->linked = true;
    return true;
}

static bool list_remove(struct list_node *node)
{
    if (node == NULL || !node->linked || node->prev == node || node->next == node) {
        return false;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list_node_init(node);
    return true;
}

enum gateway_flag {
    GATEWAY_FLAG_ENABLED = UINT32_C(1) << 0,
    GATEWAY_FLAG_DIAGNOSTIC = UINT32_C(1) << 1,
    GATEWAY_FLAG_VERBOSE = UINT32_C(1) << 2,
    GATEWAY_FLAG_ALLOWED = GATEWAY_FLAG_ENABLED |
                           GATEWAY_FLAG_DIAGNOSTIC |
                           GATEWAY_FLAG_VERBOSE
};

static bool flags_set(uint32_t *state, uint32_t mask)
{
    if (state == NULL || (mask & ~((uint32_t)GATEWAY_FLAG_ALLOWED)) != 0U) {
        return false;
    }
    *state |= mask;
    return true;
}

static bool flag_test_u32(uint32_t state, uint32_t mask)
{
    return (state & mask) == mask;
}

#define FLAG_TEST(state, mask) \
    _Generic((state), uint32_t: flag_test_u32)((state), (mask))

enum reading_kind {
    READING_TEMPERATURE,
    READING_STATUS
};

struct reading {
    enum reading_kind kind;
    union {
        int32_t temperature;
        uint32_t status;
    } value;
};

struct packet {
    uint16_t type;
    size_t len;
    unsigned char bytes[];
};

static struct packet *packet_create(uint16_t type,
                                    const unsigned char *bytes,
                                    size_t len)
{
    struct packet *packet;

    if ((len != 0U && bytes == NULL) || len > SIZE_MAX - sizeof(*packet)) {
        return NULL;
    }
    packet = malloc(sizeof(*packet) + len);
    if (packet == NULL) {
        return NULL;
    }
    packet->type = type;
    packet->len = len;
    if (len != 0U) {
        memcpy(packet->bytes, bytes, len);
    }
    return packet;
}

struct layout_probe {
    unsigned ready : 1;
    unsigned code : 3;
};

int main(void)
{
    const uint16_t samples[] = {10U, 20U, 30U};
    struct byte_vector vector;
    struct list_node active;
    struct record first = {.id = 1};
    struct record second = {.id = 2};
    struct list_node *cursor;
    struct reading reading = {
        .kind = READING_TEMPERATURE,
        .value.temperature = 42
    };
    const unsigned char payload[] = {'a', 'b', 'c'};
    struct packet *packet;
    struct packet *empty_packet;
    uint32_t flags = 0U;
    int id_sum = 0;

    assert(vector_init(&vector, sizeof(samples[0])));
    for (size_t index = 0; index < 3U; ++index) {
        assert(vector_push(&vector, &samples[index]));
    }
    assert(*(const uint16_t *)vector_at(&vector, 0U) == 10U);
    assert(*(const uint16_t *)vector_at(&vector, 2U) == 30U);
    {
        void *const data_before = vector.data;
        const size_t len_before = vector.len;
        const size_t cap_before = vector.cap;

        fail_next_allocation = true;
        assert(!vector_reserve(&vector, cap_before + 1U));
        assert(vector.data == data_before);
        assert(vector.len == len_before);
        assert(vector.cap == cap_before);
    }

    list_head_init(&active);
    list_node_init(&first.active_link);
    list_node_init(&second.active_link);
    assert(list_insert_tail(&active, &first.active_link));
    assert(list_insert_tail(&active, &second.active_link));
    assert(!list_insert_tail(&active, &first.active_link));
    for (cursor = active.next; cursor != &active; cursor = cursor->next) {
        const struct list_node *const_cursor = cursor;
        const struct record *record =
            CONTAINER_OF_CONST(const_cursor, struct record, active_link);
        id_sum += record->id;
    }

    assert(flags_set(&flags, GATEWAY_FLAG_ENABLED | GATEWAY_FLAG_VERBOSE));
    assert(FLAG_TEST(flags, (uint32_t)GATEWAY_FLAG_ENABLED));
    assert(!flags_set(&flags, UINT32_C(1) << 31));

    packet = packet_create(7U, payload, sizeof(payload));
    assert(packet != NULL);
    assert(packet->len <= (size_t)INT_MAX);
    empty_packet = packet_create(9U, NULL, 0U);
    assert(empty_packet != NULL);
    assert(packet_create(9U, payload, SIZE_MAX) == NULL);

    printf("vector=%" PRIu16 ",%" PRIu16 ",%" PRIu16 "\n",
           *(const uint16_t *)vector_at(&vector, 0U),
           *(const uint16_t *)vector_at(&vector, 1U),
           *(const uint16_t *)vector_at(&vector, 2U));
    printf("list_id_sum=%d flags=0x%08" PRIx32 "\n", id_sum, flags);
    printf("reading_temperature=%" PRId32 " packet=%.*s\n",
           reading.value.temperature, (int)packet->len, packet->bytes);
    printf("layout_probe_bytes=%zu (implementation-specific)\n",
           sizeof(struct layout_probe));

    assert(list_remove(&first.active_link));
    assert(list_remove(&second.active_link));
    free(empty_packet);
    free(packet);
    vector_destroy(&vector);
    puts("S04_CASE_PASS");
    return 0;
}
