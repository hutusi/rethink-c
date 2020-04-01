#include "skip_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_skip_list_insert()
{
    SkipList *list = skip_list_new(int_compare, NULL, NULL, 5);
    int arr[] = {5,  6,  3,  2,  8,  1,  4,  0,  9,  7,  13, 11, 14,
                 18, 19, 17, 16, 12, 15, 10, 23, 21, 24, 28, 29, 27,
                 26, 22, 25, 20, 33, 31, 34, 38, 39, 37, 36, 32, 35,
                 30, 43, 41, 44, 48, 49, 47, 46, 42, 45, 40};

    // assert(skip_list_insert(list, &(arr[0]), &(arr[0])));
    for (int i = 0; i < 50; ++i) {
        int *key = &(arr[i]);
        int *value = key;
        assert(skip_list_insert(list, key, value));
    }

    skip_list_print(list);

    SkipListNode *node = skip_list_remove_node(list, &(arr[9]));
    skip_list_free_node(list, node);

    skip_list_print(list);

    skip_list_free(list);
}

void test_skip_list()
{
    test_skip_list_insert();
}
