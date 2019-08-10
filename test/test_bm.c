#include "bm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_helper.h"
#include "alloc-testing.h"

void test_bm_string_match()
{
    assert(bm_string_match("abcabc", "abc") == 0);
    assert(bm_string_match("abcabc", "abcd") < 0);
    assert(bm_string_match("abcabcd", "abcd") == 3);
    assert(bm_string_match("bcabaaaa", "aaaa") == 4);
    // assert(bm_string_match("bbcabcdababcdabcdabde", "abcdabd") == 13);
}

void test_bm()
{
    test_bm_string_match();
}
