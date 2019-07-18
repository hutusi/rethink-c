#include "bignum.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alloc-testing.h"

void test_bignum_int_addition()
{
    char sum[100];
    assert(bignum_int_addition("123", "123", sum) > 0);
    assert(strcmp(sum, "246") == 0);
    assert(bignum_int_addition("55555", "999999999976", sum) > 0);
    assert(strcmp(sum, "1000000055531") == 0);
    assert(bignum_int_addition("1111", "111", sum) > 0);
    assert(strcmp(sum, "1222") == 0);
}

void test_bignum_int_subtraction()
{
    char diff[100];
    assert(bignum_int_subtraction("123", "123", diff) > 0);
    assert(strcmp(diff, "0") == 0);
    assert(bignum_int_subtraction("246", "123", diff) > 0);
    assert(strcmp(diff, "123") == 0);
    assert(bignum_int_subtraction("999999999976", "99999", diff) > 0);
    assert(strcmp(diff, "999999899977") == 0);
}
