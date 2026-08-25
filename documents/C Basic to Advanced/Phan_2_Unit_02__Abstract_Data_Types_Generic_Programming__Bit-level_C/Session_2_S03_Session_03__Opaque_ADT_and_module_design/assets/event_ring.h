#ifndef ADVC_EVENT_RING_H
#define ADVC_EVENT_RING_H

#include <stddef.h>
#include <stdint.h>

typedef struct event_ring event_ring;

typedef struct {
    uint32_t id;
    int32_t value;
} event_record;

typedef enum {
    RING_OK = 0,
    RING_INVALID_ARGUMENT,
    RING_OUT_OF_MEMORY,
    RING_EMPTY,
    RING_FULL
} ring_status;

/* The ring owns its backing storage and copies event values.
 * A returned handle is invalid after ring_destroy.
 * ring_reset invalidates logical contents, not the handle.
 * This API is not thread-safe; callers must synchronize shared access. */
ring_status ring_create(size_t capacity, event_ring **out_ring);
void ring_destroy(event_ring *ring);
size_t ring_capacity(const event_ring *ring);
size_t ring_size(const event_ring *ring);
ring_status ring_push(event_ring *ring, const event_record *event);
ring_status ring_peek(const event_ring *ring, event_record *out_event);
ring_status ring_pop(event_ring *ring, event_record *out_event);
ring_status ring_reset(event_ring *ring);

#endif
