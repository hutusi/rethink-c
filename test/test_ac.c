#include "ac.h"
#include "text.h"
#include "hash_table.h"
#include "arraylist.h"
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

static HashTable *ac_trie_matct_str(ACTrie *trie, const char *str)
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

void test_ac_trie_match_simple()
{
    ACTrie *trie = ac_trie_new();
    ac_trie_insert_str(trie, "li");
    ac_trie_insert_str(trie, "she");
    ac_trie_insert_str(trie, "her");
    ac_trie_set_failure(trie);
    HashTable *match_table = ac_trie_matct_str(trie, "lisherliso");
    ASSERT_INT_EQ(hash_table_size(match_table), 3);

    Text *key = text_from("li");
    ArrayList *match = (ArrayList *)hash_table_get(match_table, key);
    ASSERT_INT_EQ(match->length, 2);
    // ASSERT_INT_POINTER_EQ(match->data[0], 4);

    text_free(key);
    hash_table_free(match_table);
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

    ac_trie_set_failure(trie);
    // ASSERT_INT_EQ(ac_trie_matct_str(trie, "let, hello, hereaser herine."), 5);
    HashTable *match_table = ac_trie_matct_str(trie, "let, hello, hereaser herine. helloherahelloheraserhihhh.");
    ASSERT_INT_EQ(hash_table_size(match_table), 4);

    /** hello: 3 her: 4 era: 2 eraser: 1 */
    Text *hello = text_from("hello");
    Text *her = text_from("her");
    Text *era = text_from("era");
    Text *eraser = text_from("eraser");
    ArrayList *match;
    match = (ArrayList *)hash_table_get(match_table, hello);
    ASSERT_INT_EQ(match->length, 3);
    ASSERT_INT_POINTER_EQ(match->data[0], 5);

    match = (ArrayList *)hash_table_get(match_table, her);
    ASSERT_INT_EQ(match->length, 4);
    ASSERT_INT_POINTER_EQ(match->data[0], 12);

    match = (ArrayList *)hash_table_get(match_table, era);
    ASSERT_INT_EQ(match->length, 2);

    match = (ArrayList *)hash_table_get(match_table, eraser);
    ASSERT_INT_EQ(match->length, 1);

    text_free(hello);
    text_free(her);
    text_free(era);
    text_free(eraser);

    hash_table_free(match_table);
    ac_trie_free(trie);
}

void test_ac()
{
    test_ac_trie_free();
    test_ac_trie_insert();
    test_ac_trie_match_simple();
    test_ac_trie_match();
}
