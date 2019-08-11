#include "bitmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_bitmap()
{
    unsigned int bitsnum = 100;
    BitMap *bitmap = bitmap_new(bitsnum);

    assert(bitmap->num_bits == bitsnum);
    assert(bitmap->num_words == bitsnum / BITS_PER_WORD + 1);

    bitmap_set_all(bitmap);

    for (int i = 0; i < bitsnum; ++i) {
        assert(bitmap_get(bitmap, i) == 1);
    }

    bitmap_clear_all(bitmap);

    for (int i = 0; i < bitsnum; ++i) {
        assert(bitmap_get(bitmap, i) == 0);
    }

    bitmap_set(bitmap, 12);
    assert(bitmap_get(bitmap, 12) == 1);
    bitmap_clear(bitmap, 12);
    assert(bitmap_get(bitmap, 12) == 0);

    BitMap *other = bitmap_new(bitsnum);
    bitmap_clear_all(other);
    bitmap_clear_all(bitmap);

    bitmap_set(bitmap, 12);
    bitmap_set(other, 12);
    bitmap_and(bitmap, other);
    assert(bitmap_get(bitmap, 12) == 1);
    bitmap_xor(bitmap, other);
    assert(bitmap_get(bitmap, 12) == 0);
    bitmap_and(bitmap, other);
    assert(bitmap_get(bitmap, 12) == 0);
    bitmap_or(bitmap, other);
    assert(bitmap_get(bitmap, 12) == 1);

    bitmap_free(bitmap);
    bitmap_free(other);
}

void test_bitmap_words()
{
    word_t flag = WORD_ALL_CLEARED;
    set_bit(&flag, 0);
    // printf("===%d====", flag);
    assert(flag == 0B00000001);
    set_bit(&flag, 1);
    assert(flag == 0B00000011);
    set_bit(&flag, 2);
    assert(flag == 0B00000111);

    clear_bit(&flag, 1);
    assert(flag == 0B00000101);

    assert(get_bit(&flag, 0) == 1);
    assert(get_bit(&flag, 1) == 0);

    flag = WORD_ALL_SETTED;
    assert(flag == 0xFFFFFFFF);

    int len = 10;
    word_t *flags = (word_t *)malloc(sizeof(word_t) * len);
    set_bitmap(flags, 10);
    for (int i = 0; i < len * BITS_PER_WORD; ++i) {
        assert(get_bit(flags, i) == 1);
    }

    clear_bitmap(flags, 10);
    for (int i = 0; i < len * BITS_PER_WORD; ++i) {
        assert(get_bit(flags, i) == 0);
    }

    free(flags);
}
