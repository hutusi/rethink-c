#include "kmp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_helper.h"
#include "alloc-testing.h"

extern int *kmp_calculate_next(const char *string, int len);

void test_kmp_calculate_next()
{
    int *next;

    next = kmp_calculate_next("abc", 3);
    assert(next[0] == 0);
    assert(next[1] == 0);
    assert(next[2] == 0);
    free(next);

    next = kmp_calculate_next("aaa", 3);
    assert(next[0] == 0);
    assert(next[1] == 1);
    assert(next[2] == 2);
    free(next);

    next = kmp_calculate_next("abababab", 8);
    assert(next[0] == 0);
    assert(next[1] == 0);
    assert(next[2] == 1);
    assert(next[3] == 2);
    assert(next[4] == 3);
    assert(next[5] == 4);
    assert(next[6] == 5);
    assert(next[7] == 6);
    free(next);

    next = kmp_calculate_next("abcdabd", 7);
    assert(next[0] == 0);
    assert(next[1] == 0);
    assert(next[2] == 0);
    assert(next[3] == 0);
    assert(next[4] == 1);
    assert(next[5] == 2);
    assert(next[6] == 0);
    free(next);

    next = kmp_calculate_next("abcabaaabcda", 12);
    assert(next[0] == 0);
    assert(next[1] == 0);
    assert(next[2] == 0);
    assert(next[3] == 1);
    assert(next[4] == 2);
    assert(next[5] == 1);
    assert(next[6] == 1);
    assert(next[7] == 1);
    assert(next[8] == 2);
    assert(next[9] == 3);
    assert(next[10] == 0);
    assert(next[11] == 1);
    free(next);
}

void test_kmp_string_match()
{
    assert(kmp_string_match("abcabc", "abc") == 0);
    assert(kmp_string_match("abcabc", "abcd") < 0);
    assert(kmp_string_match("abcabcd", "abcd") == 3);
    assert(kmp_string_match("bcabaaaa", "aaaa") == 4);
    assert(kmp_string_match("bbcabcdababcdabcdabde", "abcdabd") == 13);
}

void test_kmp()
{
    test_kmp_calculate_next();
    test_kmp_string_match();
}
