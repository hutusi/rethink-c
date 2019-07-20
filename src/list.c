/**
 * @file list.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to list.h
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "list.h"
#include <stdlib.h>
#include <string.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

List *list_new()
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

void list_free(List *list)
{
    ListNode *node = list->head;

    while (node != NULL) {
        ListNode *next = node->next;
        free(node);
        node = next;
    }

    free(list);
}

static ListNode *listnode_new(ListValue data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

int list_append(List *list, ListValue data)
{
    ListNode *node = listnode_new(data);
    if (node == NULL) {
        return -1;
    }

    if (list->length == 0) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    node->prev = list->tail;
    list->tail = node;
    ++(list->length);
    return 0;
}

int list_prepend(List *list, ListValue data)
{
    ListNode *node = listnode_new(data);
    if (node == NULL) {
        return -1;
    }

    if (list->length == 0) {
        list->tail = node;
    } else {
        list->head->prev = node;
    }

    node->next = list->head;
    list->head = node;
    ++(list->length);
    return 0;
}

ListNode *list_nth_node(List *list, unsigned int n)
{
    if (list == NULL) {
        return NULL;
    }

    ListNode *node = list->head;
    for (unsigned int i = 0; i < n; ++i) {
        if (node == NULL) {
            return NULL;
        } else {
            node = node->next;
        }
    }

    return node;
}

ListValue list_nth_data(List *list, unsigned int n)
{
    ListNode *node = list_nth_node(list, n);

    if (node == NULL) {
        return LIST_NULL;
    } else {
        return node->data;
    }
}

ListValue *list_to_array(List *list)
{
    if (list == NULL) {
        return NULL;
    }

    ListValue *array = (ListValue *)malloc(list->length * sizeof(ListValue));
    if (array == NULL) {
        return NULL;
    }

    ListNode *rover = list->head;
    for (int i = 0; i < list->length; ++i) {
        array[i] = rover->data;
        rover = rover->next;
    }

    return array;
}

ListNode *list_find_node(List *list, ListNode *node)
{
    if (list == NULL || node == NULL) {
        return NULL;
    }

    ListNode *rover;
    for (rover = list->head; rover != NULL; rover = rover->next) {
        if (node == rover) {
            return node;
        }
    }

    return NULL;
}

ListNode *list_find_data(List *list, ListEqualFunc callback, ListValue data)
{
    if (list == NULL) {
        return NULL;
    }

    ListNode *rover;
    for (rover = list->head; rover != NULL; rover = rover->next) {
        if (callback(rover->data, data)) {
            return rover;
        }
    }

    return NULL;
}

ListNode *list_remove_node(List *list, ListNode *node)
{
    if (list->head == node) {
        list->head = node->next;
    }

    if (list->tail == node) {
        list->tail = node->prev;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    --(list->length);
    return node;
}

int list_remove_data(List *list, ListEqualFunc callback, ListValue data)
{
    ListNode *node = list_find_data(list, callback, data);
    if (node == NULL) {
        return -1; // not found
    }

    node = list_remove_node(list, node);
    if (node != NULL) {
        free(node);
    }
    return 0;
}

static ListNode *list_split_mid_node(ListNode *head)
{
    ListNode *fast = head->next;
    ListNode *slow = head->next;
    ListNode *prev = head;

    while (1) {
        if (fast == NULL)
            break;
        fast = fast->next;
        if (fast == NULL)
            break;
        fast = fast->next;

        prev = slow;
        slow = slow->next;
    }

    prev->next = NULL; // cut the list
    return slow;
}

static ListNode *
list_merge(ListNode *head1, ListNode *head2, ListCompareFunc compare_func)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    ListNode *new_head, *tmp;
    if (compare_func(head1->data, head2->data) <= 0) {
        new_head = head1;
        head1 = head1->next;
    } else {
        new_head = head2;
        head2 = head2->next;
    }

    tmp = new_head;
    while (head1 != NULL && head2 != NULL) {
        if (compare_func(head1->data, head2->data) <= 0) {
            tmp->next = head1;
            head1 = head1->next;
        } else {
            tmp->next = head2;
            head2 = head2->next;
        }

        tmp->next->prev = tmp;
        tmp = tmp->next;
    }

    if (head1 == NULL && head2 == NULL) {
        tmp->next = NULL;
    } else if (head1 == NULL) {
        tmp->next = head2;
        tmp->next->prev = tmp;
    } else if (head2 == NULL) {
        tmp->next = head1;
        tmp->next->prev = tmp;
    }

    return new_head;
}

ListNode *merge_sort(ListNode *head, ListCompareFunc compare_func)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode *head1 = head;
    ListNode *head2 = list_split_mid_node(head);
    head1 = merge_sort(head1, compare_func);
    head2 = merge_sort(head2, compare_func);
    return list_merge(head1, head2, compare_func);
}

int list_sort(List *list, ListCompareFunc compare_func)
{
    ListNode *new_head = merge_sort(list->head, compare_func);
    list->head = new_head;
    list->tail = list_nth_node(list, list->length);
    return 0;
}
