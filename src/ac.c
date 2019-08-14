/**
 * @file ac.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to ac.h
 * @date 2019-08-13
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "ac.h"
#include "compare.h"
#include "def.h"
#include "hash.h"
#include "queue.h"
#include <stdlib.h>

static ACTrieNode *ac_trie_new_node(char ch)
{
    ACTrieNode *node = (ACTrieNode *)malloc(sizeof(ACTrieNode));
    node->data = ch;
    node->ending = false;
    node->height = 0;
    node->failure = NULL;

    node->children = hash_table_new(
        hash_char,
        char_equal,
        free,
        NULL); /** value will be freed in root's recursive free func. */
    return node;
}

ACTrie *ac_trie_new()
{
    ACTrie *trie = (ACTrie *)malloc(sizeof(ACTrie));
    trie->root = ac_trie_new_node((char)0);
    return trie;
}

static void ac_trie_free_node(ACTrieNode *node)
{
    hash_table_free(node->children);
    free(node);
}

static void ac_trie_free_node_recursive(ACTrieNode *node)
{
    if (node == NULL)
        return;

    HashTableEntity *iterator = hash_table_first_entity(node->children);
    while (iterator != NULL) {
        HashTableEntity *prev = iterator;
        iterator = hash_table_next_entity(node->children, prev);

        ACTrieNode *child = (ACTrieNode *)(prev->value);
        ac_trie_free_node_recursive(child);
    }

    hash_table_free(node->children);
    free(node);
}

void ac_trie_free(ACTrie *trie)
{
    // free root node will free all nodes
    ac_trie_free_node_recursive(trie->root);
    free(trie);
}

static char *ac_trie_char_dup(char value)
{
    char *dup = (char *)malloc(sizeof(char));
    *dup = value;
    return dup;
}

int ac_trie_insert(ACTrie *trie, const char *str, unsigned int len)
{
    ACTrieNode *rover = trie->root;
    for (int i = 0; i < len; ++i) {
        ACTrieNode *node = hash_table_get(rover->children, (void *)&(str[i]));
        if (node == HASH_TABLE_VALUE_NULL) {
            node = ac_trie_new_node(str[i]);
            node->height = i + 1;
            hash_table_insert(rover->children, ac_trie_char_dup(str[i]), node);
        }
        rover = node;
    }

    rover->ending = true;
    return 0;
}

static void ac_trie_delete_node(ACTrie *trie,
                                ACTrieNode *parent,
                                const char *str,
                                unsigned int len,
                                unsigned int index)
{
    ACTrieNode *node = hash_table_get(parent->children, (void *)&(str[index]));
    if (node == HASH_TABLE_VALUE_NULL) {
        return;
    }

    if (index < len - 1) {
        ac_trie_delete_node(trie, node, str, len, index + 1);
    }

    if (node->children == NULL || hash_table_size(node->children) == 0) {
        hash_table_delete(parent->children, &(node->data));
        ac_trie_free_node(node);
    }
}

int ac_trie_delete(ACTrie *trie, const char *str, unsigned int len)
{
    ac_trie_delete_node(trie, trie->root, str, len, 0);
    return 0;
}

ACTrieNode *ac_trie_last_node(ACTrie *trie, const char *str, unsigned int len)
{
    ACTrieNode *rover = trie->root;
    for (int i = 0; i < len; ++i) {
        ACTrieNode *node = hash_table_get(rover->children, (void *)&(str[i]));
        if (node == HASH_TABLE_VALUE_NULL) {
            return NULL;
        }
        rover = node;
    }
    return rover;
}

bool ac_trie_include(ACTrie *trie, const char *str, unsigned int len)
{
    ACTrieNode *last = ac_trie_last_node(trie, str, len);
    return last != NULL && last->ending == true;
}

static void ac_trie_push_to_queue(Queue *queue, ACTrieNode *node)
{
    for (HashTableEntity *iterator = hash_table_first_entity(node->children);
         iterator != NULL;
         iterator = hash_table_next_entity(node->children, iterator)) {
        queue_push_tail(queue, iterator->value);
    }
}

void ac_trie_setout(ACTrie *trie)
{
    Queue *queue = queue_new();
    ac_trie_push_to_queue(queue, trie->root);
    trie->root->failure = trie->root;

    while (!queue_is_empty(queue)) {
        ACTrieNode *node = (ACTrieNode *)queue_pop_head(queue);
        ac_trie_push_to_queue(queue, node);

        for (HashTableEntity *iterator =
                 hash_table_first_entity(node->children);
             iterator != NULL;
             iterator = hash_table_next_entity(node->children, iterator)) {
            ACTrieNode *child = iterator->value;

            if (node == trie->root) {
                child->failure = trie->root;
            } else {
                ACTrieNode *failure = node->failure;
                while (failure != trie->root) {
                    ACTrieNode *next = (ACTrieNode *)hash_table_get(
                        failure->children, &(child->data));
                    if (next == NULL) {
                        failure = failure->failure;
                    } else {
                        child->failure = next;
                        break;
                    }
                }

                if (child->failure == NULL) {
                    ACTrieNode *next = (ACTrieNode *)hash_table_get(
                        failure->children, &(child->data));
                    if (next == NULL) {
                        failure = trie->root;
                    } else {
                        child->failure = next;
                    }
                }
            }
        }
    }
}

int ac_trie_match(ACTrie *trie, const char *text, unsigned int len)
{
    int count = 0;

    ACTrieNode *rover = trie->root;
    for (unsigned int i = 0; i < len; ++i) {
        do {
            ACTrieNode *next =
                (ACTrieNode *)hash_table_get(rover->children, (void *)&(text[i]));
            if (next == NULL) {
                rover = rover->failure;
            } else {
                rover = next;

                if (rover->ending) {
                    ++count;
                }
                break;
            }
        } while (rover != trie->root);
    }

    return count;
}
