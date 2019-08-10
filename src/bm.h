/**
 * @file bm.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief BM (Boyer-Moore) algorithm.
 *
 * @date 2019-08-10
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_BM_H
#define RETHINK_C_BM_H

/**
 * @brief BM algorithm to find the match substring.
 *
 * @param text      The text string.
 * @param pattern   The pattern string.
 * @return int      The first match index.
 */
int bm_string_match(const char *text, const char *pattern);

#endif /* #ifndef RETHINK_C_BM_H */
