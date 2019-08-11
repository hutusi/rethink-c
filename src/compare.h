/**
 * @file compare.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Compare & Equal functions (between two pointers).
 *
 * @date 2019-08-11
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_COMPARE_H
#define RETHINK_C_COMPARE_H

/**
 * @brief Equal function of two integers.
 *
 * @param address1  The first integer pointer address.
 * @param address2  The second integer pointer address.
 * @return int      1 if equal, otherwise 0.
 */
int int_equal(void *address1, void *address2);

/**
 * @brief Compare function of two integers.
 *
 * @param address1  The first integer pointer address.
 * @param address2  The second integer pointer address.
 * @return int      0 if equal, -1 if first less than second, 1 if first greater
 *                  than second.
 */
int int_compare(void *address1, void *address2);

/**
 * @brief Equal function of two chars.
 *
 * @param address1  The first char pointer address.
 * @param address2  The second char pointer address.
 * @return int      1 if equal, otherwise 0.
 */
int char_equal(void *address1, void *address2);

/**
 * @brief Compare function of two chars.
 *
 * @param address1  The first char pointer address.
 * @param address2  The second char pointer address.
 * @return int      0 if equal, -1 if first less than second, 1 if first greater
 *                  than second.
 */
int char_compare(void *address1, void *address2);

#endif /* #ifndef RETHINK_C_COMPARE_H */
