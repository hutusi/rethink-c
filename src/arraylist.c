/**
 * @file arraylist.c
 * 
 * @author hutusi (hutusi@outlook.com)
 * 
 * @brief Automatically resizing array(stack) 
 * 
 * @copyright Copyright (c) 2019, hutusi.com
 * 
 */

#include "arraylist.h"
#include "def.h"
#include <stdlib.h>
#include <string.h>

ArrayList *arraylist_new(unsigned int length)
{
    ArrayList *new_arraylist;
    if (length <= 0) {
        length = 16;
    }
    new_arraylist = (ArrayList *)malloc(sizeof(ArrayList));
    if (new_arraylist == NULL) {
        return NULL;
    }

    new_arraylist->_allocated = length;
    new_arraylist->length = 0;

    new_arraylist->data = malloc(length * sizeof(ArrayListValue));
    if (new_arraylist->data == NULL) {
        free(new_arraylist);
        return NULL;
    }

    return new_arraylist;
}

void arraylist_free(ArrayList *arraylist)
{
    if (arraylist != NULL) {
        free(arraylist->data);
        free(arraylist);
    }
}

static int arraylist_enlarge(ArrayList *arraylist)
{
    ArrayListValue *data;
    unsigned int newsize;

    newsize = arraylist->_allocated * 2;
    data = realloc(arraylist->data, sizeof(ArrayListValue) * newsize);

    if (data == NULL) {
        return -1;
    } else {
        arraylist->data = data;
        arraylist->_allocated = newsize;
        return 0;
    }
}

int arraylist_insert(ArrayList *arraylist,
                     unsigned int index,
                     ArrayListValue data)
{
    if (index < 0 || index > arraylist->length) {
        return -1;
    }

    if (arraylist->_allocated < arraylist->length + 1) {
        if (arraylist_enlarge(arraylist) != 0) {
            return -1;
        }
    }

    memmove(&arraylist->data[index + 1],
            &arraylist->data[index],
            (arraylist->length - index) * sizeof(ArrayListValue));

    arraylist->data[index] = data;
    arraylist->length += 1;

    return 0;
}

int arraylist_append(ArrayList *arraylist, ArrayListValue data)
{
    return arraylist_insert(arraylist, arraylist->length, data);
}

int arraylist_prepend(ArrayList *arraylist, ArrayListValue data)
{
    return arraylist_insert(arraylist, 0, data);
}

int arraylist_push(ArrayList *arraylist, ArrayListValue data)
{
    return arraylist_insert(arraylist, arraylist->length, data);
}

ArrayListValue arraylist_pop(ArrayList *arraylist)
{
    --(arraylist->length);
    return arraylist->data[arraylist->length];
}

int arraylist_remove_range(ArrayList *arraylist,
                           unsigned int index,
                           unsigned int length)
{
    if (index >= arraylist->length) {
        return -1;
    }

    if (length > arraylist->length - index) {
        return -1;
    }

    memmove(&arraylist->data[index],
            &arraylist->data[index + length],
            (arraylist->length - (index + length)) * sizeof(ArrayListValue));
    arraylist->length -= length;
    return 0;
}

int arraylist_remove(ArrayList *arraylist, unsigned int index)
{
    return arraylist_remove_range(arraylist, index, 1);
}

void arraylist_clear(ArrayList *arraylist) { arraylist->length = 0; }

int arraylist_index_of(ArrayList *arraylist,
                       ArrayListValueCompareFunc callback,
                       ArrayListValue data)
{
    int index;

    if (callback == NULL) {
        return -1;
    }

    for (index = 0; index < arraylist->length; ++index) {
        if (callback(arraylist->data[index], data) == 0) {
            return index;
        }
    }

    return -1;
}

#define swap_with_tmp(a, b, tmp) \
    if (a != b) {                \
        tmp = a;                 \
        a = b;                   \
        b = tmp;                 \
    }

/**
 * @brief Sort internal function.
 * 
 * Use quick sort.
 * 
 * @param list_data 
 * @param list_length 
 * @param compare_func 
 * @return int 
 */
static int arraylist_sort_internal(ArrayListValue *list_data,
                                   unsigned int list_length,
                                   ArrayListValueCompareFunc compare_func)
{
    ArrayListValue pivot, tmp;
    unsigned int i, left_length, right_length;

    if (list_length <= 1) {
        return 0;
    }

    pivot = list_data[list_length - 1];
    left_length = 0;

    for (i = 0; i < list_length - 1; ++i) {
        if (compare_func(list_data[i], pivot) < 0) {
            swap_with_tmp(list_data[left_length], list_data[i], tmp);
            ++left_length;
        } else {
            // do nothing
        }
    }
    swap_with_tmp(list_data[left_length], list_data[list_length - 1], tmp);
    right_length = list_length - left_length - 1; // 1 for pivot

    if (left_length > 1) {
        arraylist_sort_internal(list_data, left_length, compare_func);
    }

    if (right_length > 1) {
        arraylist_sort_internal(
            &list_data[left_length + 1], right_length, compare_func);
    }

    return 0;
}

int arraylist_sort(ArrayList *arraylist, ArrayListValueCompareFunc compare_func)
{
    return arraylist_sort_internal(
        arraylist->data, arraylist->length, compare_func);
}
