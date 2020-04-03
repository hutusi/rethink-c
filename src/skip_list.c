/**
 * @file skip_list.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to skip_list.h
 * @date 2020-03-29
 *
 * @copyright Copyright (c) 2020, hutusi.com
 *
 */

/**
 * The implementaion of skip list reference to:
 * https://www.geeksforgeeks.org/skip-list/
 * 
 */

#include "skip_list.h"
#include "def.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SKIP_LIST_NIL NULL

static SkipListNode *
skip_list_node_new(int level, SkipListKey key, SkipListValue value)
{
    SkipListNode *node = (SkipListNode *)malloc(sizeof(SkipListNode));

    node->key = key;
    node->value = value;

    node->next_array =
        (SkipListNode **)malloc((level + 1) * sizeof(SkipListNode *));
    for (int i = 0; i <= level; i++) {
        node->next_array[i] = NULL;
    }

    return node;
}

void skip_list_free_node(SkipList *list, SkipListNode *node)
{
    if (list->free_key_func && node->value) {
        list->free_key_func(node->key);
    }

    if (list->free_value_func && node->value) {
        list->free_value_func(node->value);
    }

    free(node->next_array);
    free(node);
}

SkipList *skip_list_new(SkipListCompareFunc compare_func,
                        SkipListFreeKeyFunc free_key_func,
                        SkipListFreeValueFunc free_value_func)
{
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->compare_func = compare_func;
    list->free_key_func = free_key_func;
    list->free_value_func = free_value_func;
    list->level = 0;

    list->head =
        skip_list_node_new(SKIP_LIST_MAX_LEVEL, SKIP_LIST_NIL, SKIP_LIST_NIL);

    return list;
}

void skip_list_free(SkipList *list)
{
    SkipListNode *node = list->head;

    while (node != NULL) {
        SkipListNode *next = node->next_array[0];
        skip_list_free_node(list, node);
        node = next;
    }

    free(list);
}

static int skip_list_random_level(SkipList *list)
{
    int level = 0;
    while ((rand() & RAND_MAX) < (RAND_MAX / SKIP_LIST_RANDOM_FACTOR)) {
        level++;
        if (level >= SKIP_LIST_MAX_LEVEL)
            break;
    }
    return level;
}

SkipListNode *
skip_list_insert(SkipList *list, SkipListKey key, SkipListValue value)
{
    SkipListNode **updates = (SkipListNode **)malloc((SKIP_LIST_MAX_LEVEL + 1) *
                                                     sizeof(SkipListNode *));

    for (int i = SKIP_LIST_MAX_LEVEL; i >= 0; i--) {
        if (i == SKIP_LIST_MAX_LEVEL) {
            updates[i] = list->head;
        } else {
            updates[i] = updates[i + 1];
        }
        SkipListNode *next = updates[i]->next_array[i];
        while (next != NULL && list->compare_func(key, next->key) > 0) {
            updates[i] = next;
            next = next->next_array[i];
        }
    }

    int level = skip_list_random_level(list);
    SkipListNode *node = skip_list_node_new(level, key, value);

    // update next_array on each level
    for (int i = 0; i <= level; i++) {
        node->next_array[i] = updates[i]->next_array[i];
        updates[i]->next_array[i] = node;
    }

    if (level > list->level)
        list->level = level;
    free(updates);

    return node;
}

SkipListNode *skip_list_remove_node(SkipList *list, SkipListKey key)
{
    SkipListNode *prev = list->head;
    for (int i = list->level; i >= 0; i--) {
        SkipListNode *next = prev->next_array[i];
        while (next != NULL) {
            int cmp = list->compare_func(key, next->key);
            if (cmp > 0) {
                prev = next;
                next = next->next_array[i];
            } else if (cmp < 0) {
                break;
            } else {
                SkipListNode **updates = (SkipListNode **)malloc(
                    (SKIP_LIST_MAX_LEVEL + 1) * sizeof(SkipListNode *));

                SkipListNode *node = next;
                updates[i] = prev;

                for (int j = i - 1; j >= 0; j--) {
                    while (prev->next_array[j] != node)
                        prev = prev->next_array[j];
                    updates[j] = prev;
                }

                // update next_array on each level
                for (int j = 0; j <= i; j++) {
                    updates[j]->next_array[j] = node->next_array[j];
                }

                for (int j = list->level; j >= 0; j--) {
                    if (list->head->next_array[j] == NULL) {
                        list->level--;
                    } else {
                        break;
                    }
                }

                free(updates);
                return node;
            }
        }
    }

    return NULL;
}

SkipListValue skip_list_find(SkipList *list, SkipListKey key)
{
    SkipListNode *prev = list->head;
    for (int i = list->level; i >= 0; i--) {
        SkipListNode *next = prev->next_array[i];
        while (next != NULL) {
            int cmp = list->compare_func(key, next->key);
            if (cmp > 0) {
                prev = next;
                next = next->next_array[i];
            } else if (cmp < 0) {
                break;
            } else {
                return next->value;
            }
        }
    }

    return SKIP_LIST_NIL;
}

void skip_list_print(SkipList *list)
{
    printf("\n Print Skip List: \n");
    for (int i = 0; i <= list->level; i++) {
        printf("Level %d: ", i);
        SkipListNode *cursor = list->head->next_array[i];
        while (cursor != NULL) {
            printf("%4d", *(int *)cursor->key);
            cursor = cursor->next_array[i];
        }
        printf("\n");
    }
}
