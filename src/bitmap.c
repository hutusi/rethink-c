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
#include "def.h"
#include <string.h>

inline void set_bit(word_t *words, unsigned int n)
{
    words[WORD_OFFSET(n)] |= ((word_t)1 << BIT_OFFSET(n));
}

inline void clear_bit(word_t *words, unsigned int n)
{
    words[WORD_OFFSET(n)] &= ~((word_t)1 << BIT_OFFSET(n));
}

inline int get_bit(word_t *words, unsigned int n)
{
    word_t bit = words[WORD_OFFSET(n)] & ((word_t)1 << BIT_OFFSET(n));
    return bit != 0;
}

inline void set_bitmap(word_t *words, unsigned int len)
{
    memset(words, 0xFF, len * sizeof(word_t));
}

inline void clear_bitmap(word_t *words, unsigned int len)
{
    memset(words, 0x00, len * sizeof(word_t));
}

BitMap *bitmap_new(unsigned int num_bits)
{
    BitMap *bitmap = (BitMap *)malloc(sizeof(BitMap));
    bitmap->num_bits = num_bits;
    if (num_bits % BITS_PER_WORD == 0) {
        bitmap->num_words = num_bits / BITS_PER_WORD;
    } else {
        bitmap->num_words = num_bits / BITS_PER_WORD + 1;
    }
    bitmap->words = (word_t *)malloc(sizeof(word_t) * bitmap->num_words);
    return bitmap;
}

void bitmap_free(BitMap *bitmap)
{
    free(bitmap->words);
    free(bitmap);
}

void bitmap_set(BitMap *bitmap, unsigned int n)
{
    set_bit(bitmap->words, n);
}

void bitmap_clear(BitMap *bitmap, unsigned int n)
{
    clear_bit(bitmap->words, n);
}

int bitmap_get(const BitMap *bitmap, unsigned int n)
{
    return get_bit(bitmap->words, n);
}

void bitmap_set_all(BitMap *bitmap)
{
    memset(bitmap->words, 0xFF, sizeof(word_t) * bitmap->num_words);
}

void bitmap_clear_all(BitMap *bitmap)
{
    memset(bitmap->words, 0x00, sizeof(word_t) * bitmap->num_words);
}

void bitmap_or(BitMap *bitmap, const BitMap *other)
{
    for (int i = 0; i< bitmap->num_words; ++i) {
        bitmap->words[i] |= other->words[i];
    }
}

void bitmap_and(BitMap *bitmap, const BitMap *other)
{
    for (int i = 0; i< bitmap->num_words; ++i) {
        bitmap->words[i] &= other->words[i];
    }
}

void bitmap_xor(BitMap *bitmap, const BitMap *other)
{
    for (int i = 0; i< bitmap->num_words; ++i) {
        bitmap->words[i] ^= other->words[i];
    }
}

unsigned int bitmap_count(const BitMap *bitmap)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < bitmap->num_bits; ++i) {
        if (bitmap_get(bitmap, i)) ++count;
    }
    return count;
}
