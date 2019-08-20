#include "sunday.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_sunday_string_match()
{
    assert(sunday_string_match("abcabc", "abc") == 0);
    assert(sunday_string_match("abcabc", "abcd") == -1);
    assert(sunday_string_match("abcabcd", "abcd") == 3);
    assert(sunday_string_match("bcabaaaa", "aaaa") == 4);
    assert(sunday_string_match("bcabaaabaaaa", "aaaa") == 8);

    ASSERT_INT_EQ(sunday_string_match("bbcabcdababcdabcdabde", "abcdabd"), 13);
    ASSERT_INT_EQ(sunday_string_match("here is a simple example", "example"), 17);

    ASSERT_INT_EQ(sunday_string_match("abcaacbabbacab", "abcbab"), -1);
    ASSERT_INT_EQ(sunday_string_match("abbadcababacab", "babac"), 7);

    ASSERT_INT_EQ(sunday_string_match("aaaaaaaaaaaaaaaa", "baaa"), -1);
    ASSERT_INT_EQ(sunday_string_match("abcacabcbcbacabc", "cbacabc"), 9);

    ASSERT_INT_EQ(sunday_string_match("ababcabcabcabc", "abcabcabc"), 2);
    ASSERT_INT_EQ(sunday_string_match("aaaabaaaaaaaaa", "baaaaaaaaa"), 4);
}

void test_sunday()
{
    test_sunday_string_match();
}
