/**
 * @file bignum.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Bitmap to store 0/1 values.
 *
 * refer to: https://stackoverflow.com/questions/1225998/what-is-a-bitmap-in-c
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_BITMAP_H
#define RETHINK_C_BITMAP_H

#include <limits.h> /* for CHAR_BIT */
#include <stdint.h> /* for uint32_t */

typedef uint32_t word_t;
enum { BITS_PER_WORD = sizeof(word_t) * CHAR_BIT };
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b) ((b) % BITS_PER_WORD)

#define WORD_ALL_CLEARED 0
#define WORD_ALL_SETTED UINT32_MAX

/**
 * @brief Set a bit to 1.
 *
 * @param words     The bitmap.
 * @param n         The nth bit to be set.
 */
void set_bit(word_t *words, unsigned int n);

/**
 * @brief Clear a bit to 0.
 *
 * @param words     The bitmap.
 * @param n         The nth bit to be set.
 */
void clear_bit(word_t *words, unsigned int n);

/**
 * @brief Get a bit value.
 *
 * @param words     The bitmap.
 * @param n         The nth bit to be get.
 * @return int      The value of the bit.
 */
int get_bit(word_t *words, unsigned int n);

/**
 * @brief Set all the bitmap's bits to 1.
 *
 * @param words     The bitmap.
 * @param num_words The length of bitmap. (Not the bits number.)
 */
void set_bitmap(word_t *words, unsigned int num_words);

/**
 * @brief Clear all the bitmap's bits to 0.
 *
 * @param words     The bitmap.
 * @param num_words The length of bitmap. (Not the bits number.)
 */
void clear_bitmap(word_t *words, unsigned int num_words);

/**
 * @brief Definition of a @ref BitMap.
 * 
 */
typedef struct _BitMap {
    word_t *words;
    /** The num count of all bits. */
    unsigned int num_bits;
    /** 
     * The num count of all words.
     * num_words may > num_bits / BITS_PER_WORD
     */
    unsigned int num_words;
} BitMap;

/**
 * @brief Allcate a new BitMap.
 * 
 * @param num_bits  The num of bits.
 * @return BitMap*  The new BitMap if success, otherwise NULL.
 */
BitMap *bitmap_new(unsigned int num_bits);

/**
 * @brief Delete a BitMap and free back memory.
 * 
 * @param bitmap    The BitMap to delete.
 */
void bitmap_free(BitMap *bitmap);

/**
 * @brief Set a bit to 1 in a BitMap by given the bit's index.
 * 
 * @param bitmap    The BitMap.
 * @param n         The bit's index.
 */
void bitmap_set(BitMap *bitmap, unsigned int n);

/**
 * @brief Clear a bit to 0 in a BitMap by given the bit's index.
 * 
 * @param bitmap    The BitMap.
 * @param n         The bit's index.
 */
void bitmap_clear(BitMap *bitmap, unsigned int n);

/**
 * @brief get a bit's value in a BitMap by given the bit's index.
 * 
 * @param bitmap    The BitMap.
 * @param n         The bit's index.
 * @return int      The bit's value, 0 or 1.
 */
int bitmap_get(const BitMap *bitmap, unsigned int n); 

/**
 * @brief Set all bits to 1 in a BitMap.
 * 
 * @param bitmap    The BitMap.
 */
void bitmap_set_all(BitMap *bitmap);

/**
 * @brief Clear all bits to 0 in a BitMap.
 * 
 * @param bitmap    The BitMap.
 */
void bitmap_clear_all(BitMap *bitmap);

/**
 * @brief Do or operation on a BitMap with other BitMap.
 * 
 * @param bitmap    The BitMap.
 * @param other     The other BitMap.
 */
void bitmap_or(BitMap *bitmap, const BitMap *other);

/**
 * @brief Do and operation on a BitMap with other BitMap.
 * 
 * @param bitmap    The BitMap.
 * @param other     The other BitMap.
 */
void bitmap_and(BitMap *bitmap, const BitMap *other);

/**
 * @brief Do xor operation on a BitMap with other BitMap.
 * 
 * @param bitmap    The BitMap.
 * @param other     The other BitMap.
 */
void bitmap_xor(BitMap *bitmap, const BitMap *other);

/**
 * @brief Count the sum of 1 value bits of a BitMap.
 * 
 * @param bitmap            The BitMap.
 * @return unsigned int     The sum.
 */
unsigned int bitmap_count(const BitMap *bitmap);

#endif /* #ifndef RETHINK_C_BITMAP_H */
