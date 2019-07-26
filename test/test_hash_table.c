#include "hash_table.h"
#include "hash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_helper.h"
#include "alloc-testing.h"

int string_equal(void *str1, void *str2)
{
    return strcmp((char *)str1, (char *)str2) == 0;
}

void test_hash_table_string()
{
    HashTable *hash_table = hash_table_new(hash_string, string_equal);
    char *key = strdup("abc");
    char *value = strdup("efg");
    assert(hash_table_insert(hash_table, key, value) == 0);
    assert(hash_table->length == 1);
    assert(strcmp(hash_table_query(hash_table, key), value) == 0);

    free(key);
    free(value);
}

void test_hash_table()
{
    test_hash_table_string();
}
