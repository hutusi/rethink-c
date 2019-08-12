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
#include <stdbool.h>

/**
 * @brief Definition of a @ref TrieNode.
 *
 */
typedef struct _TrieNode {
    /** Value of the node. */
    char data;
    bool ending;
    HashTable *children;
} TrieNode;

/**
 * @brief Definition of a @ref Trie.
 *
 */
typedef struct _Trie {
    TrieNode *root;
} Trie;

/**
 * @brief Allcate a new Trie.
 *
 * @return Trie*        The new Trie if success, otherwise NULL.
 */
Trie *trie_new();

/**
 * @brief Delete a Trie and free back memory.
 *
 * @param trie      The Trie to delete.
 */
void trie_free(Trie *trie);

/**
 * @brief Insert a string into a Trie.
 *
 * @param trie  The Trie.
 * @param str   The string.
 * @param len   The length of the string.
 * @return int  0 if success.
 */
int trie_insert(Trie *trie, const char *str, unsigned int len);

/**
 * @brief Delete a string into a Trie.
 *
 * Just mark the ending as 'false'.
 *
 * @param trie  The Trie.
 * @param str   The string.
 * @param len   The length of the string.
 * @return int  0 if success.
 */
int trie_delete(Trie *trie, const char *str, unsigned int len);

/**
 * @brief Check if a Trie include a string (full match).
 *
 * @param trie      The Trie.
 * @param str       The string.
 * @param len       The length of the string.
 * @return true     Include a full match.
 * @return false    Not include a full match.
 */
bool trie_include(Trie *trie, const char *str, unsigned int len);

/**
 * @brief Get the last node of a Trie by a string.
 *
 * @param trie          The Trie.
 * @param str           The string.
 * @param len           The length of the string.
 * @return TrieNode*    The last match node.
 */
TrieNode *trie_last_node(Trie *trie, const char *str, unsigned int len);

#endif /* #ifndef RETHINK_C_TRIE_H */
