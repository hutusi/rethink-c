#include "text.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"
#include "test_helper.h"

static void test_text_new()
{
    Text *text = text_new();
    ASSERT_INT_EQ(text_length(text), 0);
    ASSERT_CHAR_EQ(text_char_at(text, 0), CHAR_NIL);
    text_free(text);
}

static void test_text_clone()
{
    Text *text = text_n_from("hello,world", 5);
    ASSERT_INT_EQ(text_length(text), 5);
    ASSERT_CHAR_EQ(text_char_at(text, 0), 'h');
    ASSERT_CHAR_EQ(text_char_at(text, 4), 'o');
    ASSERT_CHAR_EQ(text_char_at(text, 5), CHAR_NIL);
    ASSERT_CHAR_EQ(text_char_at(text, 6), CHAR_NIL);

    Text *clone = text_clone(text);
    ASSERT_INT_EQ(text_length(clone), 5);
    ASSERT_CHAR_EQ(text_char_at(clone, 0), 'h');
    ASSERT_CHAR_EQ(text_char_at(clone, 4), 'o');
    ASSERT_CHAR_EQ(text_char_at(clone, 5), CHAR_NIL);
    ASSERT_CHAR_EQ(text_char_at(clone, 6), CHAR_NIL);

    text_free(text);
    text_free(clone);
}

void test_text_compare()
{
    Text *text1 = text_from("hello, world");
    Text *text2 = text_from("hello, world, my world.");
    assert(!text_equal(text1, text2));
    ASSERT_INT_EQ(text_compare(text1, text2), -1);

    Text *text3 = text_n_from("hello, world, my world.", 12);
    assert(text_equal(text1, text3));

    text_free(text1);
    text_free(text2);
    text_free(text3);
}

void test_text()
{
    test_text_new();
    test_text_clone();
    test_text_compare();
}
