/**
 * @file heap.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to heap.h
 * @date 2019-07-31
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "heap.h"
#include "def.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Heap *heap_new(HeapType type,
               HeapCompareFunc compare_func,
               HeapFreeValueFunc free_value_func)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->type = type;
    heap->compare_func = compare_func;
    heap->free_value_func = free_value_func;
    heap->num_data = 0;

    heap->_allocated = 16;
    heap->data = (HeapValue *)malloc(sizeof(HeapValue) * heap->_allocated);

    return heap;
}

void heap_free(Heap *heap)
{
    // free all data
    for (unsigned int i = 0; i < heap->num_data; ++i) {
        if (heap->free_value_func && heap->data[i]) {
            heap->free_value_func(heap->data[i]);
        }
    }
    free(heap->data);
    free(heap);
}

static int heap_enlarge(Heap *heap)
{
    HeapValue *data;
    unsigned int newsize;

    newsize = heap->_allocated * 2;
    data = realloc(heap->data, sizeof(HeapValue) * newsize);

    if (data == NULL) {
        return -1;
    } else {
        heap->data = data;
        heap->_allocated = newsize;
        return 0;
    }
}

static inline int heap_is_correct_order(Heap *heap, int front, int back)
{
    if (heap->type == MIN_HEAP) {
        return heap->compare_func(heap->data[front], heap->data[back]) <= 0;
    } else {
        return heap->compare_func(heap->data[front], heap->data[back]) >= 0;
    }
}

static inline void heap_swap(Heap *heap, int index1, int index2)
{
    HeapValue tmp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = tmp;
}

/**
 * @brief heapify bottom-up
 *
 * @param heap
 *
 * heapify swap will go through 11 -> 5 -> 2 -> 0, until done.
 *
 *                    0[#]
 *                 /       \
 *                1         2[#]
 *              /   \      /   \
 *             3    4     5[#]  6
 *            / \  / \   /
 *           7  8  9 10 11[*]
 *
 */
static inline void heap_insert_heapify(Heap *heap)
{
    int index = heap->num_data - 1;
    while (index >= 0 && !heap_is_correct_order(heap, (index - 1) / 2, index)) {
        heap_swap(heap, (index - 1) / 2, index);
        if (index == 0)
            break;
        index = (index - 1) / 2;
    }
}

int heap_insert(Heap *heap, HeapValue value)
{
    if (heap->num_data >= heap->_allocated) {
        heap_enlarge(heap);
    }

    heap->data[heap->num_data] = value;
    ++(heap->num_data);

    heap_insert_heapify(heap);
    return 0;
}

static inline int heap_pop_select_index(Heap *heap, int index)
{
    if (index >= heap->num_data) {
        return -1;
    } else if (index + 1 >= heap->num_data) {
        return index;
    } else {
        int cmp = heap->compare_func(heap->data[index], heap->data[index + 1]);
        if (heap->type == MIN_HEAP) {
            return cmp < 0 ? index : (index + 1);
        } else {
            return cmp > 0 ? index : (index + 1);
        }
    }
}

/**
 * @brief heapify top-down
 *
 * @param heap
 *
 * heapfiy swap will go through:
 *       0 -> MAX[1, 2]
 *          if 1 -> MAX[3,4]
 *          if 3 -> MAX[7,8], until done.
 *
 *               0[*]
 *             /     \
 *           1[#]     2[#]
 *          /  \      /  \
 *        3[#] 4[#]  5    6
 *       /  \
 *     7[#]  8[#]
 */
static inline void heap_pop_heapify(Heap *heap)
{
    int index = 0;
    while (1) {
        int select = heap_pop_select_index(heap, index * 2 + 1);
        if (select < 0) {
            break;
        }

        if (!heap_is_correct_order(heap, index, select)) {
            heap_swap(heap, index, select);
            index = select;
        } else {
            break;
        }
    }
}

HeapValue heap_pop(Heap *heap)
{
    if (heap->num_data <= 0) {
        return HEAP_VALUE_NULL;
    }

    HeapValue top = heap->data[0];
    heap->data[0] = heap->data[heap->num_data - 1];
    --(heap->num_data);

    heap_pop_heapify(heap);
    return top;
}
