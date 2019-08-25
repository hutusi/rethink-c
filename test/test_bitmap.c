#include "bitmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_bitmap_basic()
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

void test_bitmap_from_word()
{
    BitMap *bitmap;
    char *string;

    bitmap = bitmap_from_word(1);
    ASSERT_INT_EQ(bitmap->num_bits, 32);
    ASSERT_INT_EQ(bitmap->num_words, 1);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "10000000000000000000000000000000");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_word(1 << 2);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "00100000000000000000000000000000");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_word(0xFFFFFFFF >> 3);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "11111111111111111111111111111000");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_word((-1));
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "11111111111111111111111111111111");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_word(((unsigned int)(-1)) >> 3);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "11111111111111111111111111111000");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_word(((unsigned int)(-1)) << 3);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, "00011111111111111111111111111111");
    free(string);
    bitmap_free(bitmap);
}

void test_bitmap_from_char()
{
    BitMap *bitmap;
    char *string;

    bitmap = bitmap_from_char('a');
    string = bitmap_to_string(bitmap);
    // 'a' => 97 => 01100001 => 10000110
    ASSERT_STRING_EQ(string, "10000110");
    free(string);
    bitmap_free(bitmap);

    bitmap = bitmap_from_char('b');
    string = bitmap_to_string(bitmap);
    // 'b' => 98 => 01100010 => 01000110
    ASSERT_STRING_EQ(string, "01000110");
    free(string);
    bitmap_free(bitmap);
}

void test_bitmap_from_string()
{
    BitMap *bitmap;
    char *string;

    char *str = "0101101110001110100010111110000111110100101010101010101";
    bitmap = bitmap_from_string(str);
    string = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(string, str);
    free(string);
    bitmap_free(bitmap);
}

void test_bitmap_equal()
{
    BitMap *bitmap1;
    BitMap *bitmap2;

    char *str = "0101101110001110100010111110000111110100101010101010101";
    bitmap1 = bitmap_from_string(str);
    bitmap2 = bitmap_from_string(str);
    ASSERT(bitmap_equal(bitmap1, bitmap2), "Same BitMaps not equal!");

    bitmap_free(bitmap2);
    char *str2 = "0101101110001110100010111110000111110100101010101010100";
    bitmap2 = bitmap_from_string(str2);
    ASSERT(!bitmap_equal(bitmap1, bitmap2), "Different BitMaps are equal!");

    bitmap_free(bitmap2);
    char *str3 = "010110111000111010001011111000011";
    bitmap2 = bitmap_from_string(str3);
    ASSERT(!bitmap_equal(bitmap1, bitmap2), "Different length BitMaps are equal!");

    bitmap_free(bitmap1);
    bitmap_free(bitmap2);
}

void test_bitmap_merege_simple()
{
    BitMap *bitmap;
    BitMap *other;
    char *string;

    /* 1 */
    bitmap = bitmap_from_string("01");
    other = bitmap_from_string("11");

    bitmap_merge(bitmap, other);
    string = bitmap_to_string(bitmap);

    ASSERT_STRING_EQ(string, "0111");

    free(string);
    bitmap_free(bitmap);

    /* 2 */
    bitmap = bitmap_from_string("011");
    other = bitmap_from_string("10100");

    bitmap_merge(bitmap, other);
    string = bitmap_to_string(bitmap);

    ASSERT_STRING_EQ(string, "01110100");

    free(string);
    bitmap_free(bitmap);
}

void test_bitmap_merege()
{
    char *str1 = "0101101110001110100010111110000111110100101010101010101";
    BitMap *bitmap = bitmap_from_string(str1);

    char *str2 = "11001000111110101000011010100000111110001000";
    BitMap *other = bitmap_from_string(str2);

    bitmap_merge(bitmap, other);
    char *string = bitmap_to_string(bitmap);

    char new_str[100];
    new_str[0] = '\0';
    strcpy(new_str, str1);
    strcat(new_str, str2);
    ASSERT_STRING_EQ(string, new_str);

    free(string);
    bitmap_free(bitmap);
}

void test_bitmap_extract()
{
    BitMap *bitmap;
    char ch;

    bitmap = bitmap_from_char('a');
    ch = bitmap_extract_char(bitmap, 0);
    ASSERT_CHAR_EQ(ch, 'a');
    bitmap_free(bitmap);

    bitmap = bitmap_new(0);
    bitmap_append(bitmap, 0);
    bitmap_append(bitmap, 0);
    bitmap_append(bitmap, 1);
    bitmap_append_char(bitmap, 'b');
    ch = bitmap_extract_char(bitmap, 3);
    ASSERT_CHAR_EQ(ch, 'b');
    bitmap_free(bitmap);

    // abcde
    bitmap = bitmap_new(0);
    bitmap_append_char(bitmap, 'a');
    bitmap_append_char(bitmap, 'd');
    bitmap_append_char(bitmap, 'c');
    bitmap_append_char(bitmap, 'b');
    bitmap_append_char(bitmap, 'e');

    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 0), 'a');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 8), 'd');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 16), 'c');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 24), 'b');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 32), 'e');
    bitmap_free(bitmap);

    // if char streach over two words
    // 01a001d1c1b
    bitmap = bitmap_new(0);
    bitmap_append(bitmap, 0);
    bitmap_append(bitmap, 1);
    bitmap_append_char(bitmap, 'a');
    bitmap_append(bitmap, 0);
    bitmap_append(bitmap, 0);
    bitmap_append(bitmap, 1);
    bitmap_append_char(bitmap, 'd');
    bitmap_append(bitmap, 1);
    bitmap_append_char(bitmap, 'c');
    bitmap_append(bitmap, 1);
    bitmap_append_char(bitmap, 'b');

    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 2), 'a');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 13), 'd');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 22), 'c');
    ASSERT_CHAR_EQ(bitmap_extract_char(bitmap, 31), 'b');
    bitmap_free(bitmap);
}

void test_bitmap()
{
    test_bitmap_basic();
    test_bitmap_from_word();
    test_bitmap_from_char();
    test_bitmap_from_string();
    test_bitmap_equal();
    test_bitmap_merege_simple();
    test_bitmap_merege();
    test_bitmap_extract();
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
