#include "kmp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_helper.h"
#include "alloc-testing.h"

void test_kmp()
{
    assert(kmp_string_match("abcabc", "abc") == 0);
    assert(kmp_string_match("abcabc", "abcd") < 0);
    assert(kmp_string_match("abcabcd", "abcd") == 3);
}
