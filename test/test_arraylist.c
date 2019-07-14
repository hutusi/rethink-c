#include "arraylist.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>

void test_arraylist()
{
    ArrayList *arraylist;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    arraylist = arraylist_new(3);
    arraylist_append(arraylist, &values[0]);
    arraylist_append(arraylist, &values[1]);

    assert(arraylist->length == 2);
    assert(arraylist->_allocated = 3);

    assert(arraylist->data[0] == &values[0]);
    assert(arraylist->data[1] == &values[1]);

    arraylist_prepend(arraylist, &values[2]);
    arraylist_prepend(arraylist, &values[3]);

    assert(arraylist->length == 4);
    assert(arraylist->_allocated = 6);
    assert(arraylist->data[0] == &values[3]);
    assert(arraylist->data[1] == &values[2]);
    assert(arraylist->data[2] == &values[0]);
    assert(arraylist->data[3] == &values[1]);

    arraylist_free(arraylist);
}

void test_arraylist_index_of(void)
{
    int entries[] = {89, 4, 23, 42, 16, 15, 8, 99, 50, 30};
    int num_entries = sizeof(entries) / sizeof(int);
    ArrayList *arraylist = arraylist_new(num_entries);

    for (int i = 0; i < num_entries; ++i) {
        arraylist_append(arraylist, &entries[i]);
    }

    for (int i = 0; i < num_entries; ++i) {
        assert(arraylist_index_of(arraylist, int_compare, &entries[i]) == i);
    }

    arraylist_free(arraylist);
}

void test_arraylist_sort(void)
{
    int entries[] = {89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4};
    int sorted[] = {4, 4, 4, 4, 8, 15, 16, 23, 30, 42, 50, 89, 99};
    unsigned int num_entries = sizeof(entries) / sizeof(int);

    ArrayList *arraylist = arraylist_new(num_entries);

    for (int i = 0; i < num_entries; ++i) {
        arraylist_prepend(arraylist, &entries[i]);
    }

    arraylist_sort(arraylist, int_compare);
    assert(arraylist->length == num_entries);

    for (int i = 0; i < num_entries; ++i) {
        int *value;

        value = (int *)arraylist->data[i];
        // printf("=== [%d],[%d]===\n", *value, sorted[i]);
        assert(*value == sorted[i]);
    }

    arraylist_free(arraylist);
}
