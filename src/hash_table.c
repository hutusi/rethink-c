/**
 * @file hash_table.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to hash_table.h
 * @date 2019-07-25
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

/**
 * @todo: 
 *  1. enlarge hash table;
 *  2. free key and value;
 *  3. inline functions.
 */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

HashTable *hash_table_new(HashTableHashFunc hash_func,
                          HashTableEqualFunc equal_func)
{
    HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
    hash_table->hash_func = hash_func;
    hash_table->equal_func = equal_func;

    /** initiate default size */
    hash_table->_allocated = 100;
    hash_table->length = 0;
    hash_table->data = (HashTableEntity **)malloc(sizeof(HashTableEntity *) *
                                                  hash_table->_allocated);
    memset(hash_table->data,
           0,
           sizeof(HashTableEntity *) * hash_table->_allocated);

    hash_table->_collisions = 0;
    return hash_table;
}

void hash_table_free(HashTable *hash_table)
{
    for (int i = 0; i < hash_table->_allocated; ++i) {
        if (hash_table->data[i]) {
            free(hash_table->data[i]);
        }
    }
    free(hash_table->data);
    free(hash_table);
}

static HashTableEntity *hash_table_new_entity(HashTableKey key,
                   HashTableValue value)
{
    HashTableEntity *entity = (HashTableEntity *)malloc(sizeof(HashTableEntity));
    entity->key = key;
    entity->value = value;
    entity->next = NULL;
    return entity;
}

static void hash_table_free_entity(HashTableEntity *entity)
{
    free(entity);
}

static inline int hash_table_hashing_key(HashTable *hash_table, HashTableKey key)
{
    return hash_table->hash_func(key) % hash_table->_allocated;
}

int hash_table_insert(HashTable *hash_table,
                   HashTableKey key,
                   HashTableValue value)
{
    if (hash_table->length > (hash_table->_allocated * 0.75)) {
        /** enlarge size */
    }

    int index = hash_table_hashing_key(hash_table, key);
    if (hash_table->data[index] == NULL) {
        hash_table->data[index] = hash_table_new_entity(key, value);
    } else {
        HashTableEntity *entity = hash_table->data[index];
        HashTableEntity *prev;
        while (entity != NULL) {
            if (hash_table->equal_func(entity->key, key)) {
                return -1; /** duplicated key */
            } else {
                prev = entity;
                entity = entity->next;
            }
        }

        /** hash collision, append */
        prev->next = hash_table_new_entity(key, value);
        ++(hash_table->_collisions);
    }

    ++(hash_table->length);
    return 0;
}

HashTableValue hash_table_query(HashTable *hash_table, HashTableKey key)
{
    int index = hash_table_hashing_key(hash_table, key);
    if (hash_table->data[index] == NULL) {
        return HASH_TABLE_VALUE_NULL;
    } else {
        HashTableEntity *entity = hash_table->data[index];
        while (entity != NULL) {
            if (hash_table->equal_func(entity->key, key)) {
                return entity->value; /** find it */
            } else {
                entity = entity->next;
            }
        }

        /** not found */
        return HASH_TABLE_VALUE_NULL;
    }
}
int hash_table_delete(HashTable *hash_table, HashTableKey key)
{
    int index = hash_table_hashing_key(hash_table, key);
    if (hash_table->data[index] == NULL) {
        return -1;
    } else {
        HashTableEntity *entity = hash_table->data[index];
        HashTableEntity *prev = NULL;
        while (entity != NULL) {
            if (hash_table->equal_func(entity->key, key)) {
                if (prev == NULL) {
                    hash_table->data[index] = NULL;
                } else {
                    prev->next = NULL;
                }
                hash_table_free_entity(entity);
                return 0;  /** find and delete it */
            } else {
                entity = entity->next;
            }
        }

        /** not found */
        return -1;
    }
}
