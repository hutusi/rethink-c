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
 *  1. reduce collisions
 */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

HashTable *hash_table_new(HashTableHashFunc hash_func,
                          HashTableEqualFunc equal_func,
                          HashTableFreeKeyFunc free_key_func,
                          HashTableFreeKeyFunc free_value_func)
{
    HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
    hash_table->hash_func = hash_func;
    hash_table->equal_func = equal_func;
    hash_table->free_key_func = free_key_func;
    hash_table->free_value_func = free_value_func;

    /** initiate default size */
    hash_table->_allocated = 16;
    hash_table->length = 0;
    hash_table->data = (HashTableEntity **)malloc(sizeof(HashTableEntity *) *
                                                  hash_table->_allocated);
    memset(hash_table->data,
           0,
           sizeof(HashTableEntity *) * hash_table->_allocated);

    hash_table->_collisions = 0;
    return hash_table;
}

static void hash_table_free_entity(HashTable *hash_table,
                                   HashTableEntity *entity)
{
    if (hash_table->free_key_func != NULL && entity->key) {
        hash_table->free_key_func(entity->key);
    }
    if (hash_table->free_value_func != NULL && entity->value) {
        hash_table->free_value_func(entity->value);
    }
    free(entity);
}

void hash_table_free(HashTable *hash_table)
{
    for (int i = 0; i < hash_table->_allocated; ++i) {
        HashTableEntity *entity = hash_table->data[i];
        while (entity) {
            HashTableEntity *prev = entity;
            entity = entity->next;
            hash_table_free_entity(hash_table, prev);
        }
    }
    free(hash_table->data);
    free(hash_table);
}

static HashTableEntity *hash_table_new_entity(HashTableKey key,
                                              HashTableValue value)
{
    HashTableEntity *entity =
        (HashTableEntity *)malloc(sizeof(HashTableEntity));
    entity->key = key;
    entity->value = value;
    entity->next = NULL;
    return entity;
}

inline int hash_table_hashing_key(HashTable *hash_table, HashTableKey key)
{
    return hash_table->hash_func(key) % hash_table->_allocated;
}

static HashTableEntity *hash_table_find_insert_place(HashTable *hash_table,
                                                     HashTableEntity *entity,
                                                     HashTableKey key)
{
    HashTableEntity *prev = NULL;
    while (entity != NULL) {
        if (hash_table->equal_func(entity->key, key)) {
            return NULL; /** duplicated key */
        } else {
            prev = entity;
            entity = entity->next;
        }
    }

    return prev;
}

static void hash_table_enlarge(HashTable *hash_table)
{
    unsigned int new_size = hash_table->_allocated * 2;
    HashTableEntity **new_data =
        (HashTableEntity **)malloc(sizeof(HashTableEntity *) * new_size);
    memset(new_data, 0, sizeof(HashTableEntity *) * new_size);

    unsigned int old_size = hash_table->_allocated;
    hash_table->_allocated = new_size;
    hash_table->_collisions = 0;

    for (unsigned int i = 0; i < old_size; ++i) {
        HashTableEntity *entity = hash_table->data[i];

        while (entity != NULL) {
            HashTableEntity *new_entity = entity;
            entity = entity->next;

            new_entity->next = NULL;
            unsigned int new_hash =
                hash_table_hashing_key(hash_table, new_entity->key);

            if (new_data[new_hash] == NULL) {
                new_data[new_hash] = new_entity;
            } else {
                HashTableEntity *prev = hash_table_find_insert_place(
                    hash_table, new_data[new_hash], new_entity->key);

                /** hash collision, append */
                prev->next = new_entity;
                ++(hash_table->_collisions);
            }
        }
    }

    free(hash_table->data); /** free old data */
    hash_table->data = new_data;
}

int hash_table_insert(HashTable *hash_table,
                      HashTableKey key,
                      HashTableValue value)
{
    if (hash_table->length > (hash_table->_allocated * 0.75)) {
        /** enlarge table */
        hash_table_enlarge(hash_table);
    }

    int index = hash_table_hashing_key(hash_table, key);
    if (hash_table->data[index] == NULL) {
        hash_table->data[index] = hash_table_new_entity(key, value);
    } else {
        HashTableEntity *prev = hash_table_find_insert_place(
            hash_table, hash_table->data[index], key);
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
                hash_table_free_entity(hash_table, entity);
                return 0; /** find and delete it */
            } else {
                entity = entity->next;
            }
        }

        /** not found */
        return -1;
    }
}
