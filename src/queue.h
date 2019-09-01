/**
 * @file queue.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Double-ended queue (Deque).
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_QUEUE_H
#define RETHINK_C_QUEUE_H

/**
 * @brief The type of a value to be stored in a @ref Queue.
 *        (void *) can be changed to int, long, or other types if needed.
 */
typedef void *QueueValue;
#define QUEUE_NULL ((void *)0)

/**
 * @brief Definition of a @ref QueueNode.
 *
 */
typedef struct _QueueNode {
    QueueValue data;
    struct _QueueNode *prev;
    struct _QueueNode *next;
} QueueNode;

/**
 * @brief Definition of a @ref Queue.
 *
 */
typedef struct _Queue {
    struct _QueueNode *head;
    struct _QueueNode *tail;
    unsigned int length;
} Queue;

/**
 * @brief Allcate a new Queue.
 *
 * @return Queue*    The new Queue if success, otherwise return NULL.
 */
Queue *queue_new();

/**
 * @brief Delete a Queue and free back memory.
 *
 * @param queue  The Queue to delete.
 */
void queue_free(Queue *queue);

/**
 * @brief Push a value to the head of a Queue.
 *
 * @param queue     The Queue.
 * @param data      The value to push.
 * @return int      0 if success.
 */
int queue_push_head(Queue *queue, QueueValue data);

/**
 * @brief Pop the head value of a Queue.
 *
 * The head QueueNode of Queue has been popped and freed back memory.
 *
 * @param queue         The Queue.
 * @return QueueValue   The popped value.
 */
QueueValue queue_pop_head(Queue *queue);

/**
 * @brief Peek the head value of a Queue.
 *
 * The head QueueNode of Queue still exists in the Queue!
 *
 * @param queue         The Queue.
 * @return QueueValue   The peeked value.
 */
QueueValue queue_peek_head(const Queue *queue);

/**
 * @brief Push a value to the tail of a Queue.
 *
 * @param queue     The Queue.
 * @param data      The value to push.
 * @return int      0 if success.
 */
int queue_push_tail(Queue *queue, QueueValue data);

/**
 * @brief Pop the head value of a Queue.
 *
 * The head QueueNode of Queue has been popped and freed back memory.
 *
 * @param queue         The Queue.
 * @return QueueValue   The popped value.
 */
QueueValue queue_pop_tail(Queue *queue);

/**
 * @brief Peek the head value of a Queue.
 *
 * The head QueueNode of Queue still exists in the Queue!
 *
 * @param queue         The Queue.
 * @return QueueValue   The peeked value.
 */
QueueValue queue_peek_tail(const Queue *queue);

/**
 * @brief Check if a Queue is empty.
 *
 * @param queue     The Queue.
 * @return int      0 if not empty, 1 if empty.
 */
int queue_is_empty(const Queue *queue);

#endif /* #ifndef RETHINK_C_QUEUE_H */
