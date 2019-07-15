#include "bitmap.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alloc-testing.h"

void test_bitmap()
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
