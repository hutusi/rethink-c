/**
 * @file dup.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Utility functions: duplicate primitive value.
 * 
 * intdup, like strdup.
 *
 * @date 2019-08-16
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_DUP_H
#define RETHINK_C_DUP_H

/**
 * @brief Duplicate a int and return it's pointer.
 * 
 * @param value     The original value.
 * @return int*     The pointer.
 */
int *intdup(int value);

/**
 * @brief Duplicate a char and return it's pointer.
 * 
 * @param value     The original value.
 * @return int*     The pointer.
 */
char *char_dup(char value);

#endif /* #ifndef RETHINK_C_DUP_H */
