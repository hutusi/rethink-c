/**
 * @file kmp.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief KMP (Knuth-Morris-Pratt) algorithm.
 *
 * @date 2019-08-07
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_KMP_H
#define RETHINK_C_KMP_H

/**
 * @brief KMP algorithm to find the match substring.
 *
 * @param text      The text string.
 * @param pattern   The pattern string.
 * @return int      The first match index.
 */
int kmp_string_match(const char *text, const char *pattern);

#endif /* #ifndef RETHINK_C_KMP_H */
