#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void check_list_integrity(List *list)
{
    ListNode *prev = NULL;
    ListNode *rover = list->head;
    int i = 0;

    while (rover != NULL) {
        assert(rover->prev == prev);
        prev = rover;
        rover = rover->next;
        ++i;
    }
    assert(list->length == i);
}

void test_list()
{
    List *list;
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list = list_new();
    list_append(list, &values[0]);
    list_append(list, &values[1]);

    assert(list->length == 2);
    // printf("==== %d == %d ====", list->head->data, &values[0]);
    assert(list->head->data == &values[0]);
    assert(list->tail->data == &values[1]);

    list_prepend(list, &values[2]);
    list_prepend(list, &values[3]);
    assert(list->length == 4);
    assert(list->head->data == &values[3]);

    list_prepend(list, &values[4]);
    list_prepend(list, &values[5]);
    assert(list->length == 6);

    // check
    check_list_integrity(list);

    // 5,4,3,2,0,1
    assert(list_nth_node(list, 0) == list->head);
    assert(list_nth_node(list, 5) == list->tail);
    assert(list_nth_node(list, 4) == list->tail->prev);
    assert(list_nth_node(list, 6) == NULL);

    // printf("==== %d == %d ====", list->head->data, &values[0]);
    assert(int_equal(list_nth_data(list, 0), list->head->data));
    assert(int_equal(list_nth_data(list, 5), list->tail->data));
    assert(int_equal(list_nth_data(list, 4), list->tail->prev->data));
    assert(list_nth_data(list, 7) == LIST_NULL);

    // ListValue *list_to_array(List *list);
    ListValue *array = list_to_array(list);
    assert(array[0] == list->head->data);
    assert(array[1] == list_nth_data(list, 1));
    assert(array[2] == list_nth_data(list, 2));
    free(array);

    ListNode *tail = list->tail;
    assert(list_find_node(list, tail) == list->tail);
    // 5,4,3,2,0,1
    assert(list_find_data(list, int_equal, &values[2]) ==
           list_nth_node(list, 3));

    ListNode *node = list_nth_node(list, 3);
    node = list_remove_node(list, node);
    free(node);
    assert(list->length == 5);
    assert(int_equal(list_nth_data(list, 3), &values[0]));
    node = list_remove_node(list, list->head);
    free(node);
    assert(list->length == 4);
    assert(int_equal(list_nth_data(list, 0), &values[4]));
    // check
    check_list_integrity(list);

    assert(list_remove_data(list, int_equal, &values[4]) == 0);
    // has been removed
    assert(list_remove_data(list, int_equal, &values[4]) == -1);
    assert(list_remove_data(list, int_equal, &values[3]) == 0);
    assert(list_remove_data(list, int_equal, &values[0]) == 0);
    assert(list_remove_data(list, int_equal, &values[1]) == 0);

    assert(list->length == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    // check
    check_list_integrity(list);

    // free list
    list_free(list);
}

void test_list_sort()
{
    int entries[] = {89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4};
    int sorted[] = {4, 4, 4, 4, 8, 15, 16, 23, 30, 42, 50, 89, 99};
    int num_entries = sizeof(entries) / sizeof(int);
    List *list = list_new();

    for (int i = 0; i < num_entries; ++i) {
        assert(list_prepend(list, &entries[i]) == 0);
    }

    list_sort(list, int_compare);
    assert(list->length == num_entries);
    // check
    check_list_integrity(list);

    for (int i = 0; i < num_entries; ++i) {
        int *value = (int *)list_nth_data(list, i);
        assert(*value == sorted[i]);
    }

    list_free(list);
}
