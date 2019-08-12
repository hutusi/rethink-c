/**
 * @file trie.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to trie.h
 * @date 2019-08-11
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "trie.h"
#include "compare.h"
#include "def.h"
#include "hash.h"
#include <stdlib.h>

static TrieNode *trie_new_node(char ch)
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->data = ch;
    node->ending = false;
    node->children = hash_table_new(
        hash_char,
        char_equal,
        free,
        NULL); /** value will be freed in root's recursive free func. */
    return node;
}

Trie *trie_new()
{
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->root = trie_new_node((char)0);
    return trie;
}

static void trie_free_node_recursive(TrieNode *node)
{
    if (node == NULL)
        return;

    HashTableEntity *iterator = hash_table_first_entity(node->children);
    while (iterator != NULL) {
        HashTableEntity *prev = iterator;
        iterator = hash_table_next_entity(node->children, prev);

        TrieNode *child = (TrieNode *)(prev->value);
        trie_free_node_recursive(child);
    }

    hash_table_free(node->children);
    free(node);
}

void trie_free(Trie *trie)
{
    // free root node will free all nodes
    trie_free_node_recursive(trie->root);
    free(trie);
}

static char *trie_char_dup(char value)
{
    char *dup = (char *)malloc(sizeof(char));
    *dup = value;
    return dup;
}

int trie_insert(Trie *trie, const char *str, unsigned int len)
{
    TrieNode *rover = trie->root;
    for (int i = 0; i < len; ++i) {
        TrieNode *node = hash_table_get(rover->children, (void *)&(str[i]));
        if (node == HASH_TABLE_VALUE_NULL) {
            node = trie_new_node(str[i]);
            hash_table_insert(rover->children, trie_char_dup(str[i]), node);
        }
        rover = node;
    }

    rover->ending = true;
    return 0;
}

TrieNode *trie_last_node(Trie *trie, const char *str, unsigned int len)
{
    TrieNode *rover = trie->root;
    for (int i = 0; i < len; ++i) {
        TrieNode *node = hash_table_get(rover->children, (void *)&(str[i]));
        if (node == HASH_TABLE_VALUE_NULL) {
            return NULL;
        }
        rover = node;
    }
    return rover;
}

int trie_delete(Trie *trie, const char *str, unsigned int len)
{
    TrieNode *last = trie_last_node(trie, str, len);
    if (last != NULL) {
        last->ending = false;
        return 0;
    } else {
        return -1;
    }
}

bool trie_include(Trie *trie, const char *str, unsigned int len)
{
    TrieNode *last = trie_last_node(trie, str, len);
    return last != NULL && last->ending == true;
}
