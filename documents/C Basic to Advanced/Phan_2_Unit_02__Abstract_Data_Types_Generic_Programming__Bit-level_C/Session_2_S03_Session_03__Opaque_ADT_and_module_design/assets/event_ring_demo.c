#include "event_ring.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    event_ring *ring = NULL;
    event_record event;
    event_record e1 = {1U, 10};
    event_record e2 = {2U, 20};
    event_record e3 = {3U, 30};
    event_record e4 = {4U, 40};

    assert(ring_create(0U, &ring) == RING_INVALID_ARGUMENT && ring == NULL);
    assert(ring_create(SIZE_MAX, &ring) == RING_INVALID_ARGUMENT && ring == NULL);
    assert(ring_create(3U, &ring) == RING_OK && ring != NULL);
    assert(ring_capacity(ring) == 3U && ring_size(ring) == 0U);
    assert(ring_pop(ring, &event) == RING_EMPTY);
    assert(ring_push(ring, &e1) == RING_OK);
    assert(ring_push(ring, &e2) == RING_OK);
    assert(ring_push(ring, &e3) == RING_OK);
    assert(ring_push(ring, &e4) == RING_FULL && ring_size(ring) == 3U);
    assert(ring_peek(ring, &event) == RING_OK && event.id == 1U);
    assert(ring_pop(ring, &event) == RING_OK && event.id == 1U);
    assert(ring_push(ring, &e4) == RING_OK);
    assert(ring_pop(ring, &event) == RING_OK && event.id == 2U);
    assert(ring_pop(ring, &event) == RING_OK && event.id == 3U);
    assert(ring_pop(ring, &event) == RING_OK && event.id == 4U);
    assert(ring_size(ring) == 0U);
    assert(ring_push(NULL, &e1) == RING_INVALID_ARGUMENT);
    assert(ring_push(ring, NULL) == RING_INVALID_ARGUMENT);
    assert(ring_reset(ring) == RING_OK && ring_size(ring) == 0U);
    ring_destroy(ring);

    puts("S03 RING PASS");
    return 0;
}
