#include "bm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

extern void
bm_calculate_bad_chars(const char *pattern, int len, int *bad_chars);
extern void
bm_calculate_good_suffixes(const char *pattern, int len, int *good_suffixes);

void test_bm_calculate_bad_chars()
{
    int bad_chars[256];
    bm_calculate_bad_chars("abcdcdddf", 9, bad_chars);
    assert(bad_chars[0] == -1);

    assert(bad_chars['a'] == 0);
    assert(bad_chars['b'] == 1);
    assert(bad_chars['c'] == 4);
    assert(bad_chars['d'] == 7);
    assert(bad_chars['e'] == -1);
    assert(bad_chars['f'] == 8);
}

void test_bm_calculate_good_suffixes()
{
    int good_suffixes[100];

    bm_calculate_good_suffixes("abcd", 4, good_suffixes);
    assert(good_suffixes[0] == -1);
    assert(good_suffixes[1] == -1);
    assert(good_suffixes[2] == -1);
    assert(good_suffixes[3] == -1);
    assert(good_suffixes[4] == -1);

    bm_calculate_good_suffixes("aaaa", 4, good_suffixes);
    assert(good_suffixes[0] == -1);
    assert(good_suffixes[1] == 2);
    assert(good_suffixes[2] == 1);
    assert(good_suffixes[3] == 0);
    assert(good_suffixes[4] == -1);

    bm_calculate_good_suffixes("ababa", 5, good_suffixes);
    assert(good_suffixes[0] == -1);
    assert(good_suffixes[1] == 2);
    assert(good_suffixes[2] == 1);
    assert(good_suffixes[3] == 0);
    assert(good_suffixes[4] == -1);
    assert(good_suffixes[5] == -1);

    bm_calculate_good_suffixes("baaa", 4, good_suffixes);
    assert(good_suffixes[0] == -1);
    assert(good_suffixes[1] == 2);
    assert(good_suffixes[2] == 1);
    assert(good_suffixes[3] == -1);
    assert(good_suffixes[4] == -1);
}

void test_bm_string_match()
{
    assert(bm_string_match("abcabc", "abc") == 0);
    assert(bm_string_match("abcabc", "abcd") == -1);
    assert(bm_string_match("abcabcd", "abcd") == 3);
    assert(bm_string_match("bcabaaaa", "aaaa") == 4);
    assert(bm_string_match("bcabaaabaaaa", "aaaa") == 8);

    ASSERT_INT_EQ(bm_string_match("bbcabcdababcdabcdabde", "abcdabd"), 13);
    ASSERT_INT_EQ(bm_string_match("here is a simple example", "example"), 17);

    ASSERT_INT_EQ(bm_string_match("abcaacbabbacab", "abcbab"), -1);
    ASSERT_INT_EQ(bm_string_match("abbadcababacab", "babac"), 7);

    ASSERT_INT_EQ(bm_string_match("aaaaaaaaaaaaaaaa", "baaa"), -1);
    ASSERT_INT_EQ(bm_string_match("abcacabcbcbacabc", "cbacabc"), 9);

    ASSERT_INT_EQ(bm_string_match("ababcabcabcabc", "abcabcabc"), 2);
    ASSERT_INT_EQ(bm_string_match("aaaabaaaaaaaaa", "baaaaaaaaa"), 4);
}

void test_bm()
{
    test_bm_calculate_bad_chars();
    test_bm_calculate_good_suffixes();
    test_bm_string_match();
}
