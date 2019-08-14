#include "ac.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"
#include "test_helper.h"

static int ac_trie_insert_str(ACTrie *trie, const char *str)
{
    return ac_trie_insert(trie, str, strlen(str));
}

// static ACTrieNode *ac_trie_find_str(ACTrie *trie, const char *str)
// {
//     return ac_trie_last_node(trie, str, strlen(str));
// }

static int ac_trie_delete_str(ACTrie *trie, const char *str)
{
    return ac_trie_delete(trie, str, strlen(str));
}

static int ac_trie_matct_str(ACTrie *trie, const char *str)
{
    return ac_trie_match(trie, str, strlen(str));
}

void test_ac_trie_free()
{
    ACTrie *trie = ac_trie_new();
    ac_trie_insert_str(trie, "hello");
    HashTableEntity *entity = hash_table_first_entity(trie->root->children);
    assert(entity != NULL);
    ASSERT_CHAR_EQ(*((char *)entity->key), 'h');
    ac_trie_free(trie);
}

void test_ac_trie_insert()
{
    ACTrie *trie = ac_trie_new();

    ac_trie_insert_str(trie, "hello");
    ac_trie_insert_str(trie, "hifi");
    ac_trie_insert_str(trie, "hi world");
    ac_trie_insert_str(trie, "here");
    ac_trie_insert_str(trie, "heroine");
    ac_trie_insert_str(trie, "legend");
    ac_trie_insert_str(trie, "kelly");

    // ACTrieNode *node;
    // HashTable *children;
    // node = ac_trie_find_str(trie, "he");
    // ASSERT_CHAR_EQ(node->data, 'e');
    // children = node->children;
    // ASSERT_INT_EQ(hash_table_size(children), 2);

    assert(ac_trie_delete_str(trie, "legend") == 0);

    ac_trie_free(trie);
}

void test_ac_trie_match()
{
    ACTrie *trie = ac_trie_new();

    ac_trie_insert_str(trie, "hello");
    ac_trie_insert_str(trie, "hifi");
    ac_trie_insert_str(trie, "her");
    ac_trie_insert_str(trie, "era");
    ac_trie_insert_str(trie, "eraser");

    ASSERT_INT_EQ(ac_trie_matct_str(trie, "let, hello, hereaser herine."), 5);

    ac_trie_free(trie);
}

void test_ac()
{
    test_ac_trie_free();
    test_ac_trie_insert();
}
