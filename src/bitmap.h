/**
 * @file bignum.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Bitmap to store 0/1 values.
 *
 * Inspired (and copied) from:
 * https://stackoverflow.com/questions/1225998/what-is-a-bitmap-in-c
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
void set_bit(word_t *words, int n);

/**
 * @brief Clear a bit to 0.
 *
 * @param words     The bitmap.
 * @param n         The nth bit to be set.
 */
void clear_bit(word_t *words, int n);

/**
 * @brief Get a bit value.
 *
 * @param words     The bitmap.
 * @param n         The nth bit to be get.
 * @return int      The value of the bit.
 */
int get_bit(word_t *words, int n);

/**
 * @brief Set all the bitmap's bits to 1.
 *
 * @param words     The bitmap.
 * @param len       The length of bitmap. (Not the bits number.)
 */
void set_bitmap(word_t *words, int len);

/**
 * @brief Clear all the bitmap's bits to 0.
 *
 * @param words     The bitmap.
 * @param len       The length of bitmap. (Not the bits number.)
 */
void clear_bitmap(word_t *words, int len);

#endif /* #ifndef RETHINK_C_BITMAP_H */
