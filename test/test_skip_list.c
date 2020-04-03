#include "skip_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_skip_list_insert()
{
    SkipList *list = skip_list_new(int_compare, NULL, NULL);
    int *arr = generate_random_numbers(0, 99);

    for (int i = 0; i < 100; ++i) {
        int *key = &(arr[i]);
        int *value = key;
        assert(skip_list_insert(list, key, value));
    }

    skip_list_print(list);

    int k = 20; 
    assert(k == *((int *)skip_list_find(list, &k)));

    SkipListNode *node = skip_list_remove_node(list, &(arr[9]));
    skip_list_free_node(list, node);

    skip_list_print(list);

    skip_list_free(list);
    free(arr);
}

void test_skip_list()
{
    test_skip_list_insert();
}
