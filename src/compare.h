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

int int_equal(void *address1, void *address2);
int int_compare(void *address1, void *address2);

int char_equal(void *address1, void *address2);
int char_compare(void *address1, void *address2);

#endif /* #ifndef RETHINK_C_COMPARE_H */
