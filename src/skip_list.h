/**
 * @file skip_list.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Skip List.
 *
 * ref: https://www.geeksforgeeks.org/skip-list/
 *
 * @date 2020-03-29
 *
 * @copyright Copyright (c) 2020, hutusi.com
 *
 */

#ifndef RETHINK_C_SKIP_LIST_H
#define RETHINK_C_SKIP_LIST_H

#define RANDOM_POINT 1 / 4

/**
 * @brief The type of a key to be stored in a @ref SkipListNode.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *SkipListKey;

/**
 * @brief The type of a key to be stored in a @ref SkipListNode.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *SkipListValue;

/**
 * @brief Definition of a @ref SkipListNode.
 *
 */
typedef struct _SkipListNode {
    SkipListKey key;
    SkipListValue value;
    struct _SkipListNode *prev;
    struct _SkipListNode **next_array;
} SkipListNode;

typedef int (*SkipListCompareFunc)(SkipListKey data1, SkipListKey data2);
typedef void (*SkipListFreeKeyFunc)(SkipListKey key);
typedef void (*SkipListFreeValueFunc)(SkipListValue value);

/**
 * @brief Definition of a @ref SkipList.
 *
 */
typedef struct _SkipList {
    /** Max level of the @ref SkipList **/
    int MAX_LEVEL;
    /** Current level of the @ref SkipList **/
    int level;
    /** The head node of the @ref SkipList **/
    SkipListNode *head;

    /** Compare two node key when do searching in SkipList. */
    SkipListCompareFunc compare_func;
    SkipListFreeKeyFunc free_key_func;
    SkipListFreeValueFunc free_value_func;
} SkipList;

/**
 * @brief Allcate a new SkipList.
 *
 * @param compare_func      Compare two node value when do searching in
 * SkipList.
 * @param free_key_func     Free key callback function.
 * @param free_value_func   Free value callback function.
 * @return SkipList*          The new SkipList if success, otherwise return
 * NULL.
 */
SkipList *skip_list_new(SkipListCompareFunc compare_func,
                        SkipListFreeKeyFunc free_key_func,
                        SkipListFreeValueFunc free_value_func,
                        int max_level);

/**
 * @brief Delete a SkipList and free back memory.
 *
 * @param list      The SkipList to delete.
 */
void skip_list_free(SkipList *list);

/**
 * @brief Free a node in a SkipList.
 *
 * @param list  The SkipList
 * @param node  The node.
 */
void skip_list_free_node(SkipList *list, SkipListNode *node);

/**
 * @brief Insert a Key/Value to a SkipList.
 *
 * @param list          The SkipList.
 * @param key           The key to insert.
 * @param value         The value to insert.
 * @return SkipListNode*  The new inserted SkipListNode if success,
 *                      otherwise return NULL.
 */
SkipListNode *
skip_list_insert(SkipList *list, SkipListKey key, SkipListValue value);

/**
 * @brief Remove a SkipListNode from a SkipList.
 *
 * @param list          The SkipList.
 * @param node          The SkipListNode.
 * @return SkipListNode*  The removed SkipListNode if success,
 *                      otherwise return NULL.
 */
SkipListNode *skip_list_remove_node(SkipList *list, SkipListNode *node);

/**
 * @brief Find a SkipListNode key in a SkipList.
 *
 * @param list          The SkipList.
 * @param key           The SkipListNode value to lookup.
 * @return SkipListNode*  The matched SkipListNode if success, otherwise NULL.
 */
SkipListNode *skip_list_find_node(SkipList *list, SkipListKey key);

/**
 * @brief Print a @ref SkipList.
 *
 * @param list          The SkipList.
 */
void skip_list_print(SkipList *list);

#endif /* #ifndef RETHINK_C_SKIP_LIST_H */
