/**
 * @file sunday.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to sunday.h
 * @date 2019-08-19
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "sunday.h"
#include "def.h"
#include <string.h>

STATIC void
sunday_calculate_bad_chars(const char *pattern, int len, int *bad_chars)
{
    for (int i = 0; i < 256; ++i) {
        bad_chars[i] = -1;
    }

    for (int i = len - 1; i >= 0; --i) {
        int ch = pattern[i];
        if (bad_chars[ch] < 0) {
            bad_chars[ch] = i;
        }
    }
}

int sunday_text_match(const char *text,
                      unsigned int text_len,
                      const char *pattern,
                      unsigned int pat_len)
{
    int bad_chars[256];
    sunday_calculate_bad_chars(pattern, pat_len, bad_chars);

    int move = 0;
    for (int i = 0; i < text_len; /* no ++i */) {
        for (int j = 0; j < pat_len; /* no ++j */) {
            if (text[i] == pattern[j]) {
                ++i;
                ++j;
            } else {
                move = pat_len - bad_chars[(int)text[pat_len + move]];
                i = move;
                j = 0;
            }
        }

        /* here means j == pat_len */
        return move;
    }

    return -1;
}

int sunday_string_match(const char *text, const char *pattern)
{
    return sunday_text_match(text, strlen(text), pattern, strlen(pattern));
}
