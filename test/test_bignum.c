#include "bignum.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc-testing.h"

void test_bignum()
{
    char num[100];

    strcpy(num, "0000000");
    assert(bignum_int_sanitize(num) == Positive);
    assert(strcmp(num, "0") == 0);

    strcpy(num, "0000123400");
    assert(bignum_int_sanitize(num) == Positive);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "+0000123400  ");
    assert(bignum_int_sanitize(num) == Positive);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "  +0000123400  ");
    assert(bignum_int_sanitize(num) == Positive);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "-0000000");
    assert(bignum_int_sanitize(num) == Negative);
    assert(strcmp(num, "0") == 0);

    strcpy(num, "-0000123400");
    assert(bignum_int_sanitize(num) == Negative);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "-0000123400  ");
    assert(bignum_int_sanitize(num) == Negative);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "  -0000123400  ");
    assert(bignum_int_sanitize(num) == Negative);
    assert(strcmp(num, "123400") == 0);

    strcpy(num, "  A-0000123400  ");
    assert(bignum_int_sanitize(num) == NaN);
    assert(strcmp(num, "0") == 0);

    strcpy(num, "");
    assert(bignum_int_sanitize(num) == NaN);
    assert(strcmp(num, "0") == 0);

    strcpy(num, "ABC");
    assert(bignum_int_sanitize(num) == NaN);
    assert(strcmp(num, "0") == 0);

    strcpy(num, "+-123");
    assert(bignum_int_sanitize(num) == NaN);
    assert(strcmp(num, "0") == 0);
}

void test_bignum_int_addition()
{
    char sum[100];
    assert(bignum_int_addition("123", "123", sum) > 0);
    assert(strcmp(sum, "246") == 0);

    assert(bignum_int_addition("55555", "999999999976", sum) > 0);
    assert(strcmp(sum, "1000000055531") == 0);

    assert(bignum_int_addition("1111", "111", sum) > 0);
    assert(strcmp(sum, "1222") == 0);

    assert(bignum_int_addition("0", "0", sum) > 0);
    assert(strcmp(sum, "0") == 0);

    assert(bignum_int_addition("0", "121", sum) > 0);
    assert(strcmp(sum, "121") == 0);
}

void test_bignum_int_subtraction()
{
    char diff[100];
    assert(bignum_int_subtraction("123", "123", diff) > 0);
    assert(strcmp(diff, "0") == 0);

    assert(bignum_int_subtraction("246", "123", diff) > 0);
    assert(strcmp(diff, "123") == 0);

    assert(bignum_int_subtraction("1234", "456", diff) > 0);
    assert(strcmp(diff, "778") == 0);

    assert(bignum_int_subtraction("0", "0", diff) > 0);
    assert(strcmp(diff, "0") == 0);

    assert(bignum_int_subtraction("999999999976", "99999", diff) > 0);
    assert(strcmp(diff, "999999899977") == 0);

    assert(bignum_int_subtraction("99999", "999999999976", diff) < 0);
    assert(strcmp(diff, "999999899977") == 0);
}

void test_bignum_int_multiplication()
{
    char prod[100];
    assert(bignum_int_multiplication("1", "1", prod) > 0);
    assert(strcmp(prod, "1") == 0);

    assert(bignum_int_multiplication("245", "121", prod) > 0);
    assert(strcmp(prod, "29645") == 0);

    assert(bignum_int_multiplication("3456789", "121", prod) > 0);
    assert(strcmp(prod, "418271469") == 0);

    assert(bignum_int_multiplication("0", "0", prod) > 0);
    assert(strcmp(prod, "0") == 0);
}

void test_bignum_int_division()
{
    char quotient[100];
    char remainder[100];
    assert(bignum_int_division("1", "1", quotient, remainder) > 0);
    assert(strcmp(quotient, "1") == 0);
    assert(strcmp(remainder, "0") == 0);

    assert(bignum_int_division("123", "12345", quotient, remainder) > 0);
    assert(strcmp(quotient, "0") == 0);
    assert(strcmp(remainder, "123") == 0);

    assert(bignum_int_division("123456789", "123", quotient, remainder) > 0);
    assert(strcmp(quotient, "1003713") == 0);
    assert(strcmp(remainder, "90") == 0);

    assert(bignum_int_division("123456789", "456", quotient, remainder) > 0);
    assert(strcmp(quotient, "270738") == 0);
    assert(strcmp(remainder, "261") == 0);

    assert(bignum_int_division("0", "12345", quotient, remainder) > 0);
    assert(strcmp(quotient, "0") == 0);
    assert(strcmp(remainder, "0") == 0);

    assert(bignum_int_division("0", "0", quotient, remainder) > 0);
    assert(strcmp(quotient, "NaN") == 0);
    assert(bignum_int_division("123", "0", quotient, remainder) > 0);
    assert(strcmp(quotient, "NaN") == 0);
}
