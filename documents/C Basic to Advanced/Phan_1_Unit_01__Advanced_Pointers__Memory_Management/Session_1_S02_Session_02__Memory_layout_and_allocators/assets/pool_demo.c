#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

enum { POOL_CAPACITY = 4, BLOCK_BYTES = 64 };

typedef union {
    max_align_t alignment;
    unsigned char bytes[BLOCK_BYTES];
} pool_slot;

typedef struct {
    pool_slot slots[POOL_CAPACITY];
    bool used[POOL_CAPACITY];
} fixed_pool;

typedef enum {
    POOL_OK = 0,
    POOL_FOREIGN_POINTER,
    POOL_DOUBLE_FREE
} pool_status;

static void pool_init(fixed_pool *pool)
{
    assert(pool != NULL);
    memset(pool, 0, sizeof *pool);
}

static void *pool_alloc(fixed_pool *pool)
{
    size_t i;

    if (pool == NULL) {
        return NULL;
    }
    for (i = 0U; i < POOL_CAPACITY; ++i) {
        if (!pool->used[i]) {
            pool->used[i] = true;
            memset(pool->slots[i].bytes, 0, BLOCK_BYTES);
            return pool->slots[i].bytes;
        }
    }
    return NULL;
}

static pool_status pool_release(fixed_pool *pool, void *pointer)
{
    size_t i;

    if (pool == NULL || pointer == NULL) {
        return POOL_FOREIGN_POINTER;
    }
    for (i = 0U; i < POOL_CAPACITY; ++i) {
        if (pointer == (void *)pool->slots[i].bytes) {
            if (!pool->used[i]) {
                return POOL_DOUBLE_FREE;
            }
            pool->used[i] = false;
            return POOL_OK;
        }
    }
    return POOL_FOREIGN_POINTER;
}

static void pool_reset(fixed_pool *pool)
{
    assert(pool != NULL);
    memset(pool->used, 0, sizeof pool->used);
}

static void encode_u32_be(uint32_t value, unsigned char output[4])
{
    output[0] = (unsigned char)(value >> 24);
    output[1] = (unsigned char)(value >> 16);
    output[2] = (unsigned char)(value >> 8);
    output[3] = (unsigned char)value;
}

typedef struct {
    uint32_t id;
    uint16_t code;
    uint8_t severity;
} command_record;

int main(void)
{
    fixed_pool pool;
    void *allocated[POOL_CAPACITY];
    void *reused;
    unsigned char wire[4];
    int foreign = 0;
    size_t i;

    pool_init(&pool);
    for (i = 0U; i < POOL_CAPACITY; ++i) {
        allocated[i] = pool_alloc(&pool);
        assert(allocated[i] != NULL);
        assert((uintptr_t)allocated[i] % _Alignof(max_align_t) == 0U);
    }
    assert(pool_alloc(&pool) == NULL);
    assert(pool_release(&pool, allocated[1]) == POOL_OK);
    reused = pool_alloc(&pool);
    assert(reused == allocated[1]);
    assert(pool_release(&pool, reused) == POOL_OK);
    assert(pool_release(&pool, reused) == POOL_DOUBLE_FREE);
    assert(pool_release(&pool, &foreign) == POOL_FOREIGN_POINTER);
    pool_reset(&pool);
    assert(pool_alloc(&pool) == allocated[0]);

    encode_u32_be(UINT32_C(0x01020304), wire);
    assert(wire[0] == 1U && wire[1] == 2U && wire[2] == 3U && wire[3] == 4U);
    assert(offsetof(command_record, code) >= sizeof(uint32_t));

    puts("S02 POOL PASS");
    return 0;
}
