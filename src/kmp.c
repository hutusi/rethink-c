/**
 * @file kmp.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to kmp.h
 * @date 2019-08-07
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "kmp.h"
#include "def.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Calculate next array
 *
 * calucate the max matched suffix substring' length.
 *
 * string: abcdabd
 *
 * a        0
 * ab       0
 * abc      0
 * abcd     0
 * abcda    1
 * abcdab   2
 * abcdabd  0
 *
 * string: ababa
 *
 * a        0
 * ab       0
 * aba      1
 * abab     2
 * ababa    3
 *
 * @param string
 * @param len
 * @return STATIC* kmp_calculate_next
 */
STATIC int *kmp_calculate_next(const char *string, int len)
{
    int *next = (int *)calloc(len, sizeof(int));
    next[0] = 0;
    int k = 0;
    for (int i = 1; i < len; ++i) {
        while (k > 0 && string[k] != string[i]) {
            k = next[k];
        }

        if (string[k] == string[i]) {
            ++k;
        }

        next[i] = k;
    }

    return next;
}

/**
 * @brief KMP algorithm
 *
 * text: bbcabcdababcdabcdabde
 * pattern: abcdabd
 *
 * !
 * bbcabcdababcdabcdabde
 * abcdabd
 *
 * step 1 ->
 *  !
 * bbcabcdababcdabcdabde
 *  abcdabd
 *
 * step 1 ->
 *   !
 * bbcabcdababcdabcdabde
 *   abcdabd
 *
 * step 1 ->
 *    !
 * bbcabcdababcdabcdabde
 *    abcdabd
 *
 * step 1 -> ... until find failure charactor 'a'-'d'
 *    !     *
 * bbcabcdababcdabcdabde
 *    abcdabd
 *
 * step next[5] = 4, then step 1... until find failure charactor 'a'-'c'
 *        ! *
 * bbcabcdababcdabcdabde
 *        abcdabd
 *
 * step next[3] = 2 ...
 *          !
 * bbcabcdababcdabcdabde
 *          abcdabd
 *
 * ......
 *
 * @param text
 * @param pattern
 * @return int
 */
int kmp_string_match(const char *text, const char *pattern)
{
    int text_len = strlen(text);
    int pat_len = strlen(pattern);
    int *next = kmp_calculate_next(pattern, pat_len);

    int index = -1;
    int j = 0;
    for (int i = 0; i < text_len; ++i) {
        if (text[i] == pattern[j]) {
            ++j;
        } else {
            if (j > 0) {
                /** C allowed n[-1] */
                j = next[j - 1];
                --i;
            }
        }

        if (j >= pat_len) {
            index = i + 1 - pat_len;
            break;
        }
    }

    free(next);
    return index;
}
