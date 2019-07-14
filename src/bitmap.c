/**
* Inspired (and copied) from:
* https://stackoverflow.com/questions/1225998/what-is-a-bitmap-in-c
*
*/

#include "bitmap.h"
#include <string.h>

void set_bit(word_t* words, int n)
{
    words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void clear_bit(word_t* words, int n)
{
    words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
}

int get_bit(word_t* words, int n)
{
    word_t bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0;
}

void set_bitmap(word_t* words, int len)
{
    memset(words, 0xFF, len * sizeof(word_t));
}

void clear_bitmap(word_t* words, int len)
{
    memset(words, 0x00, len * sizeof(word_t));
}
