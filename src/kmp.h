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
 * @param text_len  The length of text.
 * @param pattern   The pattern string.
 * @param pat_len   The length of pattern string.
 * @return int      The first match index, -1 if no match.
 */
int kmp_text_match(const char *text,
                   unsigned int text_len,
                   const char *pattern,
                   unsigned int pat_len);

/**
 * @brief KMP algorithm to find the match substring.
 *
 * @param text      The text string.
 * @param pattern   The pattern string.
 * @return int      The first match index, -1 if no match.
 */
int kmp_string_match(const char *text, const char *pattern);

#endif /* #ifndef RETHINK_C_KMP_H */
