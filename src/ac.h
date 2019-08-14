/**
 * @file ac.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief AC (Aho-Corasick) algorithm. (AC ACTrie Tree).
 *
 * @date 2019-08-13
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_AC_H
#define RETHINK_C_AC_H

#include "hash_table.h"
#include <stdbool.h>

/**
 * @brief Definition of a @ref ACTrieNode.
 *
 */
typedef struct _ACTrieNode {
    /** Value of the node. */
    char data;
    bool ending;
    unsigned int height;
    HashTable *children;
    struct _ACTrieNode *failure;
} ACTrieNode;

/**
 * @brief Definition of a @ref ACTrie.
 *
 */
typedef struct _ACTrie {
    ACTrieNode *root;
} ACTrie;

typedef struct _String {
    /** The pattern string. */
    char *data;
    /** The length of pattern string. */
    unsigned int length;
} String;

/**
 * @brief Allcate a new ACTrie.
 *
 * @return ACTrie*      The new ACTrie if success, otherwise NULL.
 */
ACTrie *ac_trie_new();

/**
 * @brief Delete a ACTrie and free back memory.
 *
 * @param ac_trie      The ACTrie to delete.
 */
void ac_trie_free(ACTrie *ac_trie);

/**
 * @brief Insert a string into a Trie.
 *
 * @param trie  The Trie.
 * @param str   The string.
 * @param len   The length of the string.
 * @return int  0 if success.
 */
int ac_trie_insert(ACTrie *trie, const char *str, unsigned int len);

/**
 * @brief Delete a string into a Trie.
 *
 * Just mark the ending as 'false'.
 *
 * @param ac_trie  The Trie.
 * @param str   The string.
 * @param len   The length of the string.
 * @return int  0 if success.
 */
int ac_trie_delete(ACTrie *trie, const char *str, unsigned int len);

void ac_trie_setout(ACTrie *trie);

int ac_trie_match(ACTrie *trie, const char *text, unsigned int len);

#endif /* #ifndef RETHINK_C_AC_H */
