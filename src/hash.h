/**
 * @file hash.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Hash functions.
 *
 * @date 2019-07-26
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_HASH_H
#define RETHINK_C_HASH_H

/**
 * @brief Calculate a integer's hash.
 * 
 * @param value             The integer.
 * @return unsigned int     The hash.
 */
unsigned int hash_int(int value);

/**
 * @brief Calculate a pointer of object's hash.
 * 
 * @param object            The pointer of object.
 * @return unsigned int     The hash.
 */
unsigned int hash_object(void *object);

/**
 * @brief Calculate a string's hash.
 * 
 * @param string            The string.
 * @return unsigned int     The hash.
 */
unsigned int hash_string(void *string);

#endif /* #ifndef RETHINK_C_HASH_H */
