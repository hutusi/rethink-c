#ifndef RETHINK_C_QUEUE_H
#define RETHINK_C_QUEUE_H

typedef void *QueueValue;
#define QUEUE_NULL ((void *)0)

typedef struct _QueueNode {
    QueueValue data;
    struct _QueueNode *prev;
    struct _QueueNode *next;
} QueueNode;

typedef struct _Queue {
    struct _QueueNode *head;
    struct _QueueNode *tail;
    unsigned int length;
} Queue;

Queue *queue_new();
void queue_free(Queue *queue);

int queue_push_head(Queue *queue, QueueValue data);
QueueValue queue_pop_head(Queue *queue);
QueueValue queue_peek_head(Queue *queue);

int queue_push_tail(Queue *queue, QueueValue data);
QueueValue queue_pop_tail(Queue *queue);
QueueValue queue_peek_tail(Queue *queue);

int queue_is_empty(Queue *queue);

#endif /* #ifndef RETHINK_C_QUEUE_H */
