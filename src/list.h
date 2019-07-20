/**
 * @file list.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Double Linked List.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_LIST_H
#define RETHINK_C_LIST_H

/**
 * @brief The type of a value to be stored in a @ref List.
 *        (void *) can be changed to int, long, or other types if needed.
 */
typedef void *ListValue;

/**
 * A null @ref ListValue.
 */
#define LIST_NULL ((void *)0)

/**
 * @brief Definition of a @ref ListNode.
 *
 */
typedef struct _ListNode {
    ListValue data;
    struct _ListNode *prev;
    struct _ListNode *next;
} ListNode;

/**
 * @brief Definition of a @ref List.
 *
 */
typedef struct _List {
    struct _ListNode *head;
    struct _ListNode *tail;
    unsigned int length;
} List;

/**
 * @brief Allcate a new List.
 *
 * @return List*    The new List if success, otherwise return NULL.
 */
List *list_new();

/**
 * @brief Delete a List and free back memory.
 *
 * @param list  The list to delete.
 */
void list_free(List *list);

/**
 * @brief Prepend a value to the beginning of a List.
 *
 * @param list      The list.
 * @param data      The value to prepend.
 * @return int      0 if success.
 */
int list_prepend(List *list, ListValue data);

/**
 * @brief Append a value to the end of a List.
 *
 * @param list      The list.
 * @param data      The value to append.
 * @return int      0 if success.
 */
int list_append(List *list, ListValue data);

/**
 * @brief Get the nth node of a List.
 *
 * @param list        The list.
 * @param n           The nth index.
 * @return ListNode*  The nth node if success, otherwise return NULL.
 */
ListNode *list_nth_node(List *list, unsigned int n);

/**
 * @brief Get the nth node value of a List.
 *
 * @param list        The list.
 * @param n           The nth index.
 * @return ListNode*  The nth node value if success, otherwise return LIST_NULL.
 */
ListValue list_nth_data(List *list, unsigned int n);

/**
 * @brief Convert an List to an array.
 *
 * The List still exists!
 *
 * @param list          The List.
 * @return ListValue*   The ListValue array if success, otherwise return NULL.
 */
ListValue *list_to_array(List *list);

typedef int (*ListCompareFunc)(ListValue value1, ListValue value2);
typedef int (*ListEqualFunc)(ListValue value1, ListValue value2);

/**
 * @brief Find a ListNode in a List.
 *
 * @param list          The List.
 * @param node          The ListNode to lookup.
 * @return ListNode*    The ListNode if success, otherwise return NULL.
 */
ListNode *list_find_node(List *list, ListNode *node);

/**
 * @brief Find the ListNode of a value in a List.
 *
 * @param list          The List.
 * @param data          The ListNode's value to lookup.
 * @return ListNode*    The ListNode if success, otherwise return NULL.
 */
ListNode *list_find_data(List *list, ListEqualFunc callback, ListValue data);

/**
 * @brief Remove a ListNode from a List.
 *
 * The ListNode still exists, not be freed.
 *
 * @param list          The List.
 * @param node          The ListNode.
 * @return ListNode*    The ListNode if success, otherwise return NULL.
 */
ListNode *list_remove_node(List *list, ListNode *node);

/**
 * @brief Remove a ListNode of a value from a List.
 *
 * The ListNode is be deleted and freed back memory.
 *
 * @param list          The List.
 * @param callback      The equal callback function.
 * @param data          The ListNode value.
 * @return int          0 if success.
 */
int list_remove_data(List *list, ListEqualFunc callback, ListValue data);

/**
 * @brief Sort a List.
 *
 * @param list          The List.
 * @param compare_func  The compare function to callback.
 * @return int          0 if success.
 */
int list_sort(List *list, ListCompareFunc compare_func);

#endif /* #ifndef RETHINK_C_LIST_H */
