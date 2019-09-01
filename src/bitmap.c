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
#include <stdlib.h>
#include <string.h>

#include "def.h"

inline void set_bit(word_t *words, unsigned int n)
{
    words[WORD_OFFSET(n)] |= ((word_t)1 << BIT_OFFSET(n));
}

inline void clear_bit(word_t *words, unsigned int n)
{
    words[WORD_OFFSET(n)] &= ~((word_t)1 << BIT_OFFSET(n));
}

inline int get_bit(const word_t *words, unsigned int n)
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

static inline unsigned int bitmap_num_words_need_by_bits(num_bits)
{
    if ((num_bits % BITS_PER_WORD) == 0) {
        return num_bits / BITS_PER_WORD;
    } else {
        return num_bits / BITS_PER_WORD + 1;
    }
}

BitMap *bitmap_new(unsigned int num_bits)
{
    BitMap *bitmap = (BitMap *)malloc(sizeof(BitMap));
    bitmap->num_bits = num_bits;
    bitmap->num_words = bitmap_num_words_need_by_bits(num_bits);
    if (bitmap->num_words == 0)
        bitmap->num_words = 1;
    bitmap->words = (word_t *)malloc(sizeof(word_t) * bitmap->num_words);
    return bitmap;
}

BitMap *bitmap_clone(const BitMap *bitmap)
{
    BitMap *clone = (BitMap *)malloc(sizeof(BitMap));
    clone->num_bits = bitmap->num_bits;
    clone->num_words = bitmap->num_words;
    clone->words = (word_t *)malloc(sizeof(word_t) * bitmap->num_words);
    memcpy(clone->words, bitmap->words, sizeof(word_t) * bitmap->num_words);
    return clone;
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
    for (int i = 0; i < bitmap->num_words; ++i) {
        bitmap->words[i] |= other->words[i];
    }
}

void bitmap_and(BitMap *bitmap, const BitMap *other)
{
    for (int i = 0; i < bitmap->num_words; ++i) {
        bitmap->words[i] &= other->words[i];
    }
}

void bitmap_xor(BitMap *bitmap, const BitMap *other)
{
    for (int i = 0; i < bitmap->num_words; ++i) {
        bitmap->words[i] ^= other->words[i];
    }
}

unsigned int bitmap_count(const BitMap *bitmap)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < bitmap->num_bits; ++i) {
        if (bitmap_get(bitmap, i))
            ++count;
    }
    return count;
}

BitMap *bitmap_append(BitMap *bitmap, int flag)
{
    if (bitmap->num_words * BITS_PER_WORD <= bitmap->num_bits) {
        ++(bitmap->num_words);
        bitmap->words =
            (word_t *)realloc(bitmap->words, sizeof(word_t) * bitmap->num_words);
    }

    if (flag) {
        set_bit(bitmap->words, bitmap->num_bits);
    } else {
        clear_bit(bitmap->words, bitmap->num_bits);
    }

    ++(bitmap->num_bits);
    return bitmap;
}

BitMap *bitmap_append_char(BitMap *bitmap, unsigned char ch)
{
    return bitmap_merge(bitmap, bitmap_from_char(ch));
}

char *bitmap_to_string(BitMap *bitmap)
{
    char *string = (char *)malloc(sizeof(char) * (bitmap->num_bits + 1));
    for (unsigned int i = 0; i < bitmap->num_bits; ++i) {
        int flag = bitmap_get(bitmap, i);
        string[i] = '0' + flag;
    }
    string[bitmap->num_bits] = '\0';
    return string;
}

BitMap *bitmap_from_string(const char *string)
{
    size_t len = strlen(string);
    BitMap *bitmap = bitmap_new(len);
    for (int i = 0; i < len; ++i) {
        if (string[i] == '0') {
            clear_bit(bitmap->words, i);
        } else {
            set_bit(bitmap->words, i);
        }
    }
    return bitmap;
}

BitMap *bitmap_from_word(word_t word)
{
    BitMap *bitmap = bitmap_new(BITS_PER_WORD);
    bitmap->words[0] = word;
    return bitmap;
}

BitMap *bitmap_from_char(unsigned char ch)
{
    BitMap *bitmap = bitmap_new(CHAR_BIT);
    memcpy(bitmap->words, &ch, 1);
    return bitmap;
}

unsigned char bitmap_extract_char(const BitMap *bitmap, unsigned int n)
{
    unsigned int word_offset = WORD_OFFSET(n);
    unsigned int bit_offset = BIT_OFFSET(n);
    unsigned int word;
    /** if char streach over two words ... */
    if (bit_offset > BITS_PER_WORD - CHAR_BIT) {
        unsigned int front_len = BITS_PER_WORD - bit_offset;
        unsigned int back_len = CHAR_BIT - (BITS_PER_WORD - bit_offset);

        unsigned int front = bitmap->words[word_offset] >> (BITS_PER_WORD - front_len);
        unsigned int back = bitmap->words[word_offset + 1] << (BITS_PER_WORD - back_len);

        word = front | (back >> (BITS_PER_WORD - back_len - front_len));
    } else {
        word = bitmap->words[word_offset] >> bit_offset;
    }

    return (unsigned char)word;
}

BitMap *bitmap_concat(BitMap *bitmap, const BitMap *other)
{
    unsigned int total_bits = bitmap->num_bits + other->num_bits;
    if (total_bits >= bitmap->num_words * BITS_PER_WORD) {
        bitmap->num_words = bitmap_num_words_need_by_bits(total_bits);
        bitmap->words = (word_t *)realloc(bitmap->words,
                                          sizeof(word_t) * bitmap->num_words);
    }

    unsigned int remainder = bitmap->num_bits % BITS_PER_WORD;
    unsigned int quotient = bitmap->num_bits / BITS_PER_WORD;
    // if target bits is 0, or full of words, just copy other words to the end.
    if (remainder == 0) {
        memcpy(&(bitmap->words[quotient]), other->words, sizeof(word_t) * other->num_words);
    } else {
        // -1: 1111 * 8 => 0001 111 ...
        bitmap->words[quotient] &= ~(((word_t)(-1)) << remainder);

        unsigned int num = bitmap_num_words_need_by_bits(bitmap->num_bits);
        if (bitmap->num_words > num) {
            memset(&(bitmap->words[num]),
                   0x0,
                   sizeof(word_t) * (bitmap->num_words - num));
        }

        for (int i = 0; i < other->num_words; ++i) {
            word_t front = other->words[i] << remainder;
            bitmap->words[quotient + i] |= front;

            if (quotient + i + 1 < bitmap->num_words) {
                word_t back = other->words[i] >> (BITS_PER_WORD - remainder);
                bitmap->words[quotient + i + 1] |= back;
            }
        }
    }

    bitmap->num_bits += other->num_bits;
    return bitmap;
}

BitMap *bitmap_merge(BitMap *bitmap, BitMap *other)
{
    bitmap_concat(bitmap, other);
    bitmap_free(other);
    return bitmap;
}

int bitmap_equal(const BitMap *bitmap1, const BitMap *bitmap2)
{
    if (bitmap1->num_bits != bitmap2->num_bits)
        return 0;

    if (bitmap1->num_words > 1) {
        if (memcmp(bitmap1->words,
                   bitmap2->words,
                   (bitmap1->num_words - 1) * sizeof(word_t)) != 0) {
            return 0;
        }
    }

    return (bitmap1->words[bitmap1->num_words - 1]
            << (BITS_PER_WORD - BIT_OFFSET(bitmap1->num_bits))) ==
           (bitmap2->words[bitmap2->num_words - 1]
            << (BITS_PER_WORD - BIT_OFFSET(bitmap2->num_bits)));
}
