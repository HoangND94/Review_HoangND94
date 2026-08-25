#include "event_ring.h"

#include <stdint.h>
#include <stdlib.h>

struct event_ring {
    event_record *items;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
};

static size_t advance_index(size_t index, size_t capacity)
{
    return (index + 1U == capacity) ? 0U : index + 1U;
}

ring_status ring_create(size_t capacity, event_ring **out_ring)
{
    event_ring *ring;

    if (out_ring == NULL) {
        return RING_INVALID_ARGUMENT;
    }
    *out_ring = NULL;
    if (capacity == 0U || capacity > SIZE_MAX / sizeof(event_record)) {
        return RING_INVALID_ARGUMENT;
    }
    ring = calloc(1U, sizeof *ring);
    if (ring == NULL) {
        return RING_OUT_OF_MEMORY;
    }
    ring->items = calloc(capacity, sizeof ring->items[0]);
    if (ring->items == NULL) {
        free(ring);
        return RING_OUT_OF_MEMORY;
    }
    ring->capacity = capacity;
    *out_ring = ring;
    return RING_OK;
}

void ring_destroy(event_ring *ring)
{
    if (ring != NULL) {
        free(ring->items);
        free(ring);
    }
}

size_t ring_capacity(const event_ring *ring)
{
    return ring == NULL ? 0U : ring->capacity;
}

size_t ring_size(const event_ring *ring)
{
    return ring == NULL ? 0U : ring->count;
}

ring_status ring_push(event_ring *ring, const event_record *event)
{
    if (ring == NULL || event == NULL) {
        return RING_INVALID_ARGUMENT;
    }
    if (ring->count == ring->capacity) {
        return RING_FULL;
    }
    ring->items[ring->tail] = *event;
    ring->tail = advance_index(ring->tail, ring->capacity);
    ring->count += 1U;
    return RING_OK;
}

ring_status ring_peek(const event_ring *ring, event_record *out_event)
{
    if (ring == NULL || out_event == NULL) {
        return RING_INVALID_ARGUMENT;
    }
    if (ring->count == 0U) {
        return RING_EMPTY;
    }
    *out_event = ring->items[ring->head];
    return RING_OK;
}

ring_status ring_pop(event_ring *ring, event_record *out_event)
{
    if (ring == NULL || out_event == NULL) {
        return RING_INVALID_ARGUMENT;
    }
    if (ring->count == 0U) {
        return RING_EMPTY;
    }
    *out_event = ring->items[ring->head];
    ring->head = advance_index(ring->head, ring->capacity);
    ring->count -= 1U;
    return RING_OK;
}

ring_status ring_reset(event_ring *ring)
{
    if (ring == NULL) {
        return RING_INVALID_ARGUMENT;
    }
    ring->head = 0U;
    ring->tail = 0U;
    ring->count = 0U;
    return RING_OK;
}
