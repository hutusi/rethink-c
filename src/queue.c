#include "queue.h"
#include <stdlib.h>
#include <string.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

Queue *queue_new()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->head = queue->tail = NULL;
    queue->length = 0;
    return queue;
}

void queue_free(Queue *queue)
{
    QueueNode *node = queue->head;

    while (node != NULL) {
        QueueNode *next = node->next;
        free(node);
        node = next;
    }

    free(queue);
}

static QueueNode *queuenode_new(QueueValue data)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

int queue_push_head(Queue *queue, QueueValue data)
{
    QueueNode *node = queuenode_new(data);
    if (node == NULL) {
        return -1;
    }

    if (queue->length == 0) {
        queue->tail = node;
    } else {
        queue->head->prev = node;
    }

    node->next = queue->head;
    queue->head = node;
    ++(queue->length);
    return 0;
}

QueueValue queue_pop_head(Queue *queue)
{
    if (queue->length == 0) {
        return QUEUE_NULL;
    }

    QueueNode *node = queue->head;
    queue->head = node->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    } else {
        queue->head->prev = NULL;
    }

    --(queue->length);
    QueueValue value = node->data;
    free(node);
    return value;
}

QueueValue queue_peek_head(Queue *queue)
{
    if (queue->length == 0) {
        return QUEUE_NULL;
    } else {
        return queue->head->data;
    }
}

int queue_push_tail(Queue *queue, QueueValue data)
{
    QueueNode *node = queuenode_new(data);
    if (node == NULL) {
        return -1;
    }

    if (queue->length == 0) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }

    node->prev = queue->tail;
    queue->tail = node;
    ++(queue->length);
    return 0;
}


QueueValue queue_pop_tail(Queue *queue)
{
    if (queue->length == 0) {
        return QUEUE_NULL;
    }

    QueueNode *node = queue->tail;
    queue->tail = node->prev;

    if (queue->tail == NULL) {
        queue->head = NULL;
    } else {
        queue->tail->next = NULL;
    }

    --(queue->length);
    QueueValue value = node->data;
    free(node);
    return value;
}

QueueValue queue_peek_tail(Queue *queue)
{
    if (queue->length == 0) {
        return QUEUE_NULL;
    } else {
        return queue->tail->data;
    }
}

int queue_is_empty(Queue *queue)
{
    return queue->length == 0;
}
