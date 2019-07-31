/**
 * @file heap.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Binary Heap.
 *
 * @date 2019-07-31
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_HEAP_H
#define RETHINK_C_HEAP_H

/**
 * @brief The type of a key to be stored in a @ref Heap.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *HeapValue;

/**
 * A null @ref HeapValue.
 */
#define HEAP_VALUE_NULL ((void *)0)

typedef int (*HeapCompareFunc)(HeapValue data1, HeapValue data2);
typedef void (*HeapFreeValueFunc)(HeapValue value);

typedef enum {
    /** Minimum heap. */
    MIN_HEAP = 0,
    /** Maximum heap. */
    MAX_HEAP = 1
} HeapType;

/**
 * @brief Definition of a @ref Heap.
 *
 */
typedef struct _Heap {
    /** Values Array of the @ref Heap. */
    HeapValue *data;
    /** Compare two entity value when do searching in Heap. */
    HeapCompareFunc compare_func;
    HeapFreeValueFunc free_value_func;

    HeapType type;
    /** The number of entitys of the @ref Heap. */
    unsigned int num_data;
    unsigned int _allocated;
} Heap;

/**
 * @brief Allcate a new Heap.
 *
 * @param type              MIN_HEAP or MAX_HEAP.
 * @param compare_func      Compare two entity value when do searching in Heap.
 * @param free_value_func   Free value callback function.
 * @return Heap*            The new Heap if success, otherwise return NULL.
 */
Heap *heap_new(HeapType type,
               HeapCompareFunc compare_func,
               HeapFreeValueFunc free_value_func);

/**
 * @brief Delete a Heap and free back memory.
 *
 * @param heap      The Heap to delete.
 */
void heap_free(Heap *heap);

/**
 * @brief Insert a HeapValue to a Heap.
 *
 * @param heap          The Heap.
 * @param data          The value to insert.
 * @return HeapEntity*  The new inserted HeapEntity if success,
 *                      otherwise return NULL.
 */
int heap_insert(Heap *heap, HeapValue data);

/**
 * @brief Pop the top HeapValue from a Heap.
 *
 * @param heap          The Heap.
 * @return HeapValue    The first HeapValue if success,
 *                      otherwise HEAP_VALUE_NULL.
 */
HeapValue heap_pop(Heap *heap);

#endif /* #ifndef RETHINK_C_HEAP_H */
