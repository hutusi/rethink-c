/**
 * @file trie.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Trie Tree.
 *
 * @date 2019-08-11
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_TRIE_H
#define RETHINK_C_TRIE_H

#include "hash_table.h"

/**
 * @brief Definition of a @ref TrieNode.
 *
 */
typedef struct _TrieNode {
    /** Value of the node. */
    char data;
    HashTable *children;
} TrieNode;

/**
 * @brief Definition of a @ref Trie.
 *
 */
typedef struct _Trie
{
    TrieNode *root;
} Trie;

/**
 * @brief Allcate a new Trie.
 *
 * @param compare_func  Compare two node value when do searching in Trie.
 * @return Trie*        The new Trie if success, otherwise NULL.
 */
Trie *trie_new();

/**
 * @brief Delete a Trie and free back memory.
 *
 * @param trie      The Trie to delete.
 */
void trie_free(Trie *trie);

int trie_insert(Trie *trie, const char *str, unsigned int len);

TrieNode *trie_find(Trie *trie, const char *str, unsigned int len);

#endif /* #ifndef RETHINK_C_TRIE_H */
