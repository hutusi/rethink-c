#include "trie.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"
#include "test_helper.h"

static int trie_insert_str(Trie *trie, const char *str)
{
    return trie_insert(trie, str, strlen(str));
}

static TrieNode *trie_find_str(Trie *trie, const char *str)
{
    return trie_find(trie, str, strlen(str));
}

void test_trie_free()
{
    Trie *trie = trie_new();
    trie_insert_str(trie, "hello");
    HashTableEntity *entity = hash_table_first_entity(trie->root->children);
    assert(entity != NULL);
    ASSERT_CHAR_EQ(*((char *)entity->key), 'h');
    trie_free(trie);
}

void test_trie_insert()
{
    Trie *trie = trie_new();

    trie_insert_str(trie, "hello");
    trie_insert_str(trie, "hifi");
    trie_insert_str(trie, "hi world");
    trie_insert_str(trie, "here");
    trie_insert_str(trie, "heroine");
    trie_insert_str(trie, "legend");
    trie_insert_str(trie, "kelly");

    TrieNode *node;
    HashTable *children;
    node = trie_find_str(trie, "he");
    ASSERT_CHAR_EQ(node->data, 'e');
    children = node->children;
    ASSERT_INT_EQ(hash_table_size(children), 2);

    trie_free(trie);
}

void test_trie()
{
    test_trie_free();
    test_trie_insert();
}
