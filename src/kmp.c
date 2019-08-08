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
#include <stdlib.h>
#include <string.h>

static void kmp_calculate_next(const char *string, int len, int *next)
{
    next[0] = 0;
    int k = 0;
    for (int i = 1; i < len; ++i) {
        while (k > 0 && next[k] != next[i]) {
            k = next[k];
        } 
        
        if (next[k + 1] != next[i]) {
            ++k;
        }

        next[i] = k;
    }
}

int kmp_string_match(const char *text, const char *pattern)
{
    int text_len = strlen(text);
    int pat_len = strlen(pattern);
    int *next = (int *)calloc(pat_len, sizeof(int));
    kmp_calculate_next(pattern, pat_len, next);

    int index = -1;
    int j = 0;
    for (int i = 0; i < text_len; ++i) {
        if (text[i] == pattern[j]) {
            ++j;
        } else {
            j = next[j];
            --i;
        }

        if (j >= pat_len) {
            index = i + 1 - pat_len;
            break;
        }
    }

    free(next);
    return index;
}
