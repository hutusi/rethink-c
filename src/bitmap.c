/**
 * @file bignum.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to bignum.h
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "bitmap.h"
#include <string.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

void set_bit(word_t *words, int n)
{
    words[WORD_OFFSET(n)] |= ((word_t)1 << BIT_OFFSET(n));
}

void clear_bit(word_t *words, int n)
{
    words[WORD_OFFSET(n)] &= ~((word_t)1 << BIT_OFFSET(n));
}

int get_bit(word_t *words, int n)
{
    word_t bit = words[WORD_OFFSET(n)] & ((word_t)1 << BIT_OFFSET(n));
    return bit != 0;
}

void set_bitmap(word_t *words, int len)
{
    memset(words, 0xFF, len * sizeof(word_t));
}

void clear_bitmap(word_t *words, int len)
{
    memset(words, 0x00, len * sizeof(word_t));
}
