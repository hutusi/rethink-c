/**
 * Inspired (and copied) from:
 * https://stackoverflow.com/questions/1225998/what-is-a-bitmap-in-c
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

void set_bit(word_t *words, int n);

void clear_bit(word_t *words, int n);

int get_bit(word_t *words, int n);

void set_bitmap(word_t *words, int len);

void clear_bitmap(word_t *words, int len);

#endif /* #ifndef RETHINK_C_BITMAP_H */
