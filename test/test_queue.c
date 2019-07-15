#include "queue.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>

void test_queue()
{
    Queue *queue;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    queue = queue_new();
    assert(queue_is_empty(queue));

    queue_push_head(queue, &values[0]);
    queue_push_head(queue, &values[1]);
    queue_push_head(queue, &values[2]);

    assert(!queue_is_empty(queue));
    assert(queue_peek_head(queue) == &values[2]);
    assert(queue_pop_head(queue) == &values[2]);
    assert(queue_pop_head(queue) == &values[1]);
    assert(queue_pop_head(queue) == &values[0]);
    assert(queue_is_empty(queue));

    queue_push_tail(queue, &values[0]);
    queue_push_tail(queue, &values[1]);
    queue_push_tail(queue, &values[2]);

    assert(queue_peek_head(queue) == &values[0]);
    assert(queue_peek_tail(queue) == &values[2]);
    assert(queue_pop_tail(queue) == &values[2]);
    assert(queue_pop_tail(queue) == &values[1]);
    assert(queue_pop_tail(queue) == &values[0]);

    queue_free(queue);
}
