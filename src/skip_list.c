/**
 * @file skip_list.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to skip_list.h
 * @date 2020-03-29
 *
 * @copyright Copyright (c) 2020, hutusi.com
 *
 */

#include "skip_list.h"
#include "def.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SKIP_LIST_NIL NULL

static SkipListNode *
skip_list_node_new(int level, SkipListKey key, SkipListValue value)
{
    SkipListNode *node = (SkipListNode *)malloc(sizeof(SkipListNode));

    node->key = key;
    node->value = value;
    node->prev = NULL;

    node->next_array =
        (SkipListNode **)malloc((level + 1) * sizeof(SkipListNode *));
    for (int i = 0; i <= level; i++) {
        node->next_array[i] = NULL;
    }

    return node;
}

static void skip_list_node_free(SkipList *list, SkipListNode *node)
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
                        SkipListFreeValueFunc free_value_func,
                        int max_level)
{
    if (max_level < 2) {
        return NULL;
    }

    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->compare_func = compare_func;
    list->free_key_func = free_key_func;
    list->free_value_func = free_value_func;
    list->MAX_LEVEL = max_level;
    list->level = 0;

    list->head =
        skip_list_node_new(list->MAX_LEVEL, SKIP_LIST_NIL, SKIP_LIST_NIL);

    return list;
}

void skip_list_free(SkipList *list)
{
    SkipListNode *node = list->head;

    while (node != NULL) {
        SkipListNode *next = node->next_array[0];
        skip_list_node_free(list, node);
        node = next;
    }

    free(list);
}

static int skip_list_random_level(SkipList *list)
{
    int level = 0;
    while ((rand() & RAND_MAX) < (RAND_MAX * RANDOM_POINT)) {
        level++;
        if (level >= list->MAX_LEVEL)
            break;
    }
    return level;
}

SkipListNode *
skip_list_insert(SkipList *list, SkipListKey key, SkipListValue value)
{
    SkipListNode **updates =
        (SkipListNode **)malloc((list->MAX_LEVEL + 1) * sizeof(SkipListNode *));

    for (int i = list->MAX_LEVEL; i >= 0; i--) {
        if (i == list->MAX_LEVEL) {
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

    // update prev on level 0
    node->prev = updates[0];
    if (updates[0]->next_array[0] != NULL)
        updates[0]->next_array[0]->prev = node;

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
