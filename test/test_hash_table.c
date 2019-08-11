#include "hash.h"
#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_hash_table_string()
{
    HashTable *hash_table =
        hash_table_new(hash_string, string_equal, free, free);
    char *key = strdup("abc");
    char *value = strdup("efg");
    assert(hash_table_insert(hash_table, key, value) == 0);
    // assert(hash_table->length == 1);
    assert(string_equal(hash_table_get(hash_table, key), value));

    key = strdup("aaaa");
    value = strdup("bbbb");
    assert(hash_table_insert(hash_table, key, value) == 0);
    // assert(hash_table->length == 2);
    assert(string_equal(hash_table_get(hash_table, key), value));

    value = strdup("new new");
    assert(hash_table_set(hash_table, "abc", value) == 0);
    // assert(hash_table->length == 2);
    assert(string_equal(hash_table_get(hash_table, "abc"), value));

    assert(hash_table_delete(hash_table, "abc") == 0);
    // assert(hash_table->length == 1);
    assert(hash_table_get(hash_table, "abc") == HASH_TABLE_VALUE_NULL);

    hash_table_free(hash_table);
}

void test_hash_table_int()
{
    HashTable *hash_table = hash_table_new(hash_int, int_equal, free, free);
    int *key = intdup(1);
    int *value = intdup(2);
    assert(hash_table_insert(hash_table, key, value) == 0);
    // assert(hash_table->length == 1);
    assert(int_equal(hash_table_get(hash_table, key), value));

    hash_table_free(hash_table);
}

#define MAX_TABLE_SIZE 10000

void test_hash_table_enlarge()
{
    char buf[10];
    HashTable *hash_table =
        hash_table_new(hash_string, string_equal, free, NULL);
    for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
        sprintf(buf, "%i", i);
        char *key = strdup(buf);
        char *value = key;

        assert(hash_table_insert(hash_table, key, value) == 0);
    }

    // ===hash_table size [10000], [16384], [4573]
    // printf("===hash_table size [%d], [%d], [%d]",
    //        hash_table->length,
    //        hash_table->_allocated,
    //        hash_table->_collisions);
    // assert(hash_table->length == MAX_TABLE_SIZE);

    for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
        sprintf(buf, "%i", i);
        assert(string_equal(hash_table_get(hash_table, buf), buf));
    }

    hash_table_free(hash_table);
}

void test_hash_table_iterate()
{
    char buf[10];
    HashTable *hash_table =
        hash_table_new(hash_string, string_equal, free, NULL);
    for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
        sprintf(buf, "%i", i);
        char *key = strdup(buf);
        char *value = key;

        assert(hash_table_insert(hash_table, key, value) == 0);
    }
    ASSERT_INT_EQ(hash_table_size(hash_table), MAX_TABLE_SIZE);

    int count = 0;
    for (HashTableEntity *iterator = hash_table_first_entity(hash_table);
         iterator != NULL;
         iterator = hash_table_next_entity(hash_table, iterator)) {
        ++count;
    }
    ASSERT_INT_EQ(count, MAX_TABLE_SIZE);

    for (HashTableEntity *iterator = hash_table_last_entity(hash_table);
         iterator != NULL;
         iterator = hash_table_prev_entity(hash_table, iterator)) {
        hash_table_delete(hash_table, iterator->key);
    }
    ASSERT_INT_EQ(hash_table_size(hash_table), 0);

    hash_table_free(hash_table);
}

void test_hash_table()
{
    test_hash_table_string();
    test_hash_table_int();
    test_hash_table_enlarge();
}
