/**
 * @file hash_table.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Hash table.
 *
 * @date 2019-07-25
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_HASH_TABLE_H
#define RETHINK_C_HASH_TABLE_H

/**
 * @brief The type of a key to be stored in a @ref HashTable.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *HashTableKey;

/**
 * @brief The type of a key to be stored in a @ref HashTable.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *HashTableValue;

/**
 * A null @ref HashTableValue.
 */
#define HASH_TABLE_VALUE_NULL ((void *)0)

/**
 * @brief Definition of a @ref HashTableEntity.
 *
 */
typedef struct _HashTableEntity {
    HashTableKey key;
    HashTableValue value;
    struct _HashTableEntity *next;
} HashTableEntity;

typedef unsigned int (*HashTableHashFunc)(HashTableKey key);
typedef int (*HashTableEqualFunc)(HashTableKey key1, HashTableKey key2);

typedef void (*HashTableFreeKeyFunc)(HashTableKey key);
typedef void (*HashTableFreeValueFunc)(HashTableValue value);

/**
 * @brief Definition of a @ref HashTable.
 *
 */
typedef struct _HashTable HashTable;

/**
 * @brief Allcate a new HashTable.
 *
 * @param hash_func         The hash function.
 * @param equal_func        The equal function that compare keys.
 * @param free_key_func     The free function that free keys.
 * @param free_value_func   The free function that free values.
 * @return HashTable*       The new HashTable if success, otherwise NULL.
 */
HashTable *hash_table_new(HashTableHashFunc hash_func,
                          HashTableEqualFunc equal_func,
                          HashTableFreeKeyFunc free_key_func,
                          HashTableFreeKeyFunc free_value_func);

/**
 * @brief Delete a HashTable and free back memory.
 *
 * @param hash_table  The HashTable to delete.
 */
void hash_table_free(HashTable *hash_table);

/**
 * @brief Insert a key/value pair to a HashTable.
 *
 * @param hash_table    The HashTable.
 * @param key           The key.
 * @param value         The value.
 * @return int          0 if success.
 */
int hash_table_insert(HashTable *hash_table,
                      HashTableKey key,
                      HashTableValue value);

/**
 * @brief Get the value by a key from a HashTable.
 *
 * @param hash_table        The HashTable.
 * @param key               The key.
 * @return HashTableValue   The value.
 */
HashTableValue hash_table_get(HashTable *hash_table, HashTableKey key);

/**
 * @brief Set a value by a key to a HashTable, insert a key/value pair if key not exists in HashTable.
 * 
 * @param hash_table    The HashTable.
 * @param key           The key.
 * @param value         The value.
 * @return int          0 if success.
 */
int hash_table_set(HashTable *hash_table,
                   HashTableKey key,
                   HashTableValue value);

/**
 * @brief Delete an entity by a key from a HashTable.
 *
 * @param hash_table    The HashTable.
 * @param key           The key.
 * @return int          0 if success.
 */
int hash_table_delete(HashTable *hash_table, HashTableKey key);

#endif /* #ifndef RETHINK_C_HASH_TABLE_H */
