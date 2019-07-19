#include "bignum.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define char_to_int(ch) (ch - '0')
#define int_to_char(ch) (ch + '0')

#define BIG_NUM_ZERO "0"
#define BIG_NUM_ONE "1"
#define BIG_NUM_NOT_A_NUM "NaN"

int bignum_int_compare_zero(const char *num)
{
    return strcmp(num, BIG_NUM_ZERO);
}

int bignum_int_compare(const char *left, const char *right)
{
    size_t left_len = strlen(left);
    size_t right_len = strlen(right);

    if (left_len < right_len) {
        return -1;
    } else if (left_len > right_len) {
        return 1;
    } else {
        return strcmp(left, right);
    }
}

static size_t bignum_int_trim_head_zero(char *num, size_t len)
{
    int zero = 0;
    for (int i = 0; i < len; ++i) {
        if (num[i] != '0') {
            break;
        } else {
            ++zero;
        }
    }

    if (zero > 0) {
        for (int i = zero; i <= len + 1; ++i) {
            num[i - zero] = num[i];
        }
    }

    return len - zero;
}

size_t static bignum_int_addition_internal(const char *addend,
                                           size_t addend_len,
                                           const char *aug,
                                           size_t aug_len,
                                           char *sum)
{
    int eval;
    int carry = 0;

    // m len + n len ==> m or m + 1 len sum
    int sum_len = addend_len + 1;
    int index = sum_len;
    sum[0] = '0';
    sum[index] = '\0';

    for (int i = 1; i <= aug_len; ++i) {
        eval = char_to_int(addend[addend_len - i]) +
               char_to_int(aug[aug_len - i]) + carry;
        carry = eval / 10;
        sum[--index] = int_to_char(eval % 10);
    }

    for (int i = addend_len - aug_len - 1; i >= 0; --i) {
        eval = char_to_int(addend[i]) + carry;
        carry = eval / 10;
        sum[--index] = int_to_char(eval % 10);
    }

    assert(index == 1);
    if (carry > 0) {
        sum[--index] = int_to_char(carry);
    } else {
        memmove(sum, &sum[1], sum_len);
        --sum_len;
    }

    return sum_len;
}

Sign bignum_int_addition(const char *addend, const char *aug, char *sum)
{
    size_t addend_len = strlen(addend);
    size_t aug_len = strlen(aug);

    if (addend_len < aug_len) {
        bignum_int_addition_internal(aug, aug_len, addend, addend_len, sum);
    } else {
        bignum_int_addition_internal(addend, addend_len, aug, aug_len, sum);
    }
    return Positive;
}

static size_t bignum_int_subtraction_internal(const char *minuend,
                                              const char *subtractor,
                                              char *difference)
{
    size_t minuend_len = strlen(minuend);
    size_t subtractor_len = strlen(subtractor);

    // m len - n len ==> diff len <= m
    int diff_len = minuend_len;
    int index = diff_len;
    difference[index] = '\0';

    int borrow = 0;
    for (int i = 1; i <= subtractor_len; ++i) {
        int m = char_to_int(minuend[minuend_len - i]) - borrow;
        int s = char_to_int(subtractor[subtractor_len - i]);
        --index;
        if (m < s) {
            difference[index] = int_to_char(10 + m - s);
            borrow = 1;
        } else {
            difference[index] = int_to_char(m - s);
            borrow = 0;
        }
    }

    for (int i = subtractor_len + 1; i <= minuend_len; ++i) {
        int m = char_to_int(minuend[minuend_len - i]) - borrow;
        --index;
        if (m < 0) {
            difference[index] = int_to_char(10 + m);
            borrow = 1;
        } else {
            difference[index] = int_to_char(m);
            borrow = 0;
        }
    }

    assert(index == 0);
    return bignum_int_trim_head_zero(difference, diff_len);
}

Sign bignum_int_subtraction(const char *minuend,
                            const char *subtractor,
                            char *difference)
{
    int cmp = bignum_int_compare(minuend, subtractor);

    if (cmp < 0) {
        bignum_int_subtraction_internal(subtractor, minuend, difference);
        return Negative;
    } else if (cmp > 0) {
        bignum_int_subtraction_internal(minuend, subtractor, difference);
        return Positive;
    } else {
        strcpy(difference, BIG_NUM_ZERO);
        return Positive;
    }
}

static size_t bignum_int_multiplication_move(char *num, size_t len, size_t move)
{
    for (size_t i = 0; i < move; ++i) {
        num[len + i] = '0';
    }
    size_t new_len = len + move;
    num[new_len] = '\0';
    return new_len;
}

static size_t bignum_int_multiplication_internal(const char *multiplicand,
                                                 size_t multiplicand_len,
                                                 const char *multiplier,
                                                 size_t multiplier_len,
                                                 char *product)
{
    int move = 0;
    int factor = 0;
    size_t product_len = multiplicand_len + multiplier_len;
    strcpy(product, BIG_NUM_ZERO);
    char *tmp_product = (char *)malloc(sizeof(char) * product_len);
    size_t tmp_product_len = 1;
    strcpy(tmp_product, BIG_NUM_ZERO);
    char *tmp_multip = (char *)malloc(sizeof(char) * product_len);
    size_t tmp_multip_len = 0;

    for (int i = multiplier_len - 1; i >= 0; --i, ++move) {
        strcpy(tmp_multip, multiplicand);
        tmp_multip_len =
            bignum_int_multiplication_move(tmp_multip, multiplicand_len, move);

        factor = char_to_int(multiplier[i]);
        for (int j = 0; j < factor; ++j) {
            strcpy(tmp_product, product);
            if (tmp_product_len < tmp_multip_len) {
                tmp_product_len = bignum_int_addition_internal(tmp_multip,
                                                               tmp_multip_len,
                                                               tmp_product,
                                                               tmp_product_len,
                                                               product);
            } else {
                tmp_product_len = bignum_int_addition_internal(tmp_product,
                                                               tmp_product_len,
                                                               tmp_multip,
                                                               tmp_multip_len,
                                                               product);
            }
        }
    }

    free(tmp_product);
    free(tmp_multip);
    return tmp_product_len;
}

Sign bignum_int_multiplication(const char *multiplicand,
                               const char *multiplier,
                               char *product)
{
    size_t multiplicand_len = strlen(multiplicand);
    size_t multiplier_len = strlen(multiplier);

    if (multiplicand_len < multiplier_len) {
        bignum_int_multiplication_internal(multiplier,
                                           multiplier_len,
                                           multiplicand,
                                           multiplicand_len,
                                           product);
    } else {
        bignum_int_multiplication_internal(multiplicand,
                                           multiplicand_len,
                                           multiplier,
                                           multiplier_len,
                                           product);
    }
    return Positive;
}

static size_t bignum_int_append_char(char *num, size_t len, char ch)
{
    int new_len = len + 1;
    num[len] = ch;
    num[new_len] = '\0';
    return new_len;
}

static void bignum_int_division_internal(const char *dividend,
                                         const char *divisor,
                                         char *quotient,
                                         char *remainder)
{
    size_t dividend_len = strlen(dividend);
    size_t divisor_len = strlen(divisor);

    char *tmp_dividend = (char *)malloc(sizeof(char) * dividend_len);
    char *tmp_diff = (char *)malloc(sizeof(char) * dividend_len);
    size_t quotient_len = 0;

    // 123456 / 789 => first try: 123 / 789 , then move to right
    size_t tmp_dividend_len =
        divisor_len - 1; // just copy 12, 3 will be append in loop
    memcpy(tmp_dividend, dividend, tmp_dividend_len);
    tmp_dividend[tmp_dividend_len] = '\0';
    for (int cursor = tmp_dividend_len; cursor < dividend_len; ++cursor) {
        tmp_dividend_len = bignum_int_append_char(
            tmp_dividend, tmp_dividend_len, dividend[cursor]);

        int times = 0;
        while (bignum_int_compare(tmp_dividend, divisor) >= 0) {
            tmp_dividend_len = bignum_int_subtraction_internal(
                tmp_dividend, divisor, tmp_diff);
            strcpy(tmp_dividend, tmp_diff);
            ++times;
        }

        if (quotient_len != 0 || times != 0) {
            quotient[quotient_len++] = int_to_char(times);
        }
    }

    quotient[quotient_len] = '\0';
    strcpy(remainder, tmp_dividend);

    free(tmp_dividend);
    free(tmp_diff);
}

Sign bignum_int_division(const char *dividend,
                         const char *divisor,
                         char *quotient,
                         char *remainder)
{
    if (bignum_int_compare_zero(divisor) == 0) {
        strcpy(quotient, BIG_NUM_NOT_A_NUM);
        strcpy(remainder, BIG_NUM_ZERO);
        return Positive;
    }

    int cmp = bignum_int_compare(dividend, divisor);

    if (cmp < 0) {
        strcpy(quotient, BIG_NUM_ZERO);
        strcpy(remainder, dividend);
    } else if (cmp > 0) {
        bignum_int_division_internal(dividend, divisor, quotient, remainder);
    } else {
        strcpy(quotient, BIG_NUM_ONE);
        strcpy(remainder, BIG_NUM_ZERO);
    }

    return Positive;
}
