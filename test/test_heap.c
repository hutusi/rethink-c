#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_heap()
{
    int arr[] = {19, 13, 5,  6, 14, 15, 20, 3, 2,  8,
                 1,  16, 17, 4, 10, 18, 9,  7, 11, 12};
    Heap *heap = heap_new(MAX_HEAP, int_compare, NULL);

    int size = sizeof(arr) / sizeof(int);
    for (int i = 0; i < size; ++i) {
        assert(heap_insert(heap, &(arr[i])) == 0);
    }

    // HeapValue top = heap_pop(heap);
    // assert(*(int *)top == 20);
    // assert(heap->num_data == 19);

    for (int i = 20; i >= 1; --i) {
        assert(heap->num_data == i);
        assert(*(int *)heap_pop(heap) == i);
    }

    heap_free(heap);
}
