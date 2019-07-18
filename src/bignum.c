#include "bignum.h"
#include <assert.h>
#include <string.h>

#define char_to_int(ch) (ch - '0')
#define int_to_char(ch) (ch + '0')

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

static void bignum_int_trim_head_zero(char *num, size_t len)
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
}

Sign static bignum_int_addition_internal(const char *addend,
                                         size_t addend_len,
                                         const char *aug,
                                         size_t aug_len,
                                         char *sum)
{
    int eval;
    int carry = 0;

    // m len + n len ==> m or m + 1 len sum
    int sum_len = addend_len + 1;
    sum[0] = '0';
    sum[sum_len] = '\0';

    for (int i = 1; i <= aug_len; ++i) {
        eval = char_to_int(addend[addend_len - i]) +
               char_to_int(aug[aug_len - i]) + carry;
        carry = eval / 10;
        sum[--sum_len] = int_to_char(eval % 10);
    }

    for (int i = aug_len; i < addend_len; ++i) {
        eval = char_to_int(addend[addend_len - i]) + carry;
        carry = eval / 10;
        sum[--sum_len] = int_to_char(eval % 10);
    }

    assert(sum_len == 1);
    if (carry > 0) {
        sum[--sum_len] = int_to_char(carry);
    } else {
        bignum_int_trim_head_zero(sum, strlen(sum));
    }

    return Positive;
}

Sign bignum_int_addition(const char *addend, const char *aug, char *sum)
{
    size_t addend_len = strlen(addend);
    size_t aug_len = strlen(aug);

    if (addend_len < aug_len) {
        return bignum_int_addition_internal(
            aug, aug_len, addend, addend_len, sum);
    } else {
        return bignum_int_addition_internal(
            addend, addend_len, aug, aug_len, sum);
    }
}

void bignum_int_subtraction_internal(const char *minuend,
                                     const char *subtractor,
                                     char *difference)
{
    size_t minuend_len = strlen(minuend);
    size_t subtractor_len = strlen(subtractor);

    int eval;
    int borrow = 0;

    // m len - n len ==> diff len <= m
    int diff_len = minuend_len;
    int index = diff_len;
    difference[index] = '\0';

    for (int i = 1; i <= subtractor_len; ++i) {
        eval = char_to_int(minuend[minuend_len - i]) -
               char_to_int(subtractor[subtractor_len - i]) - borrow;
        if (eval < 0) {
            eval += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        difference[--index] = int_to_char(eval);
    }

    for (int i = subtractor_len; i < minuend_len; ++i) {
        eval = char_to_int(minuend[minuend_len - i]) - borrow;
        if (eval < 0) {
            eval += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        difference[--index] = int_to_char(eval);
    }

    assert(index == 0);
    bignum_int_trim_head_zero(difference, diff_len);
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
        difference[0] = '0';
        difference[1] = '\0';
        return Positive;
    }
}

Sign bignum_int_multiplication(char *multiplicand,
                               char *multiplier,
                               char *product)
{
}

Sign bignum_int_division(char *dividend,
                         char *divisor,
                         char *quotient,
                         char *remainder)
{
}