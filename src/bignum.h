#ifndef RETHINK_C_BIGNUM_H
#define RETHINK_C_BIGNUM_H

typedef enum _Sign { Positive = 1, Negative = -1, NaN = 0 } Sign;

typedef struct _BigNum {
    char *number;
    char *integer;
    unsigned int num_int;
    char *decimal;
    unsigned int num_dec;
    Sign sign;
} BigNum;

BigNum *bignum_new(char *num);
void bignum_free(BigNum *bignum);

int bignum_int_compare_zero(const char *num);
int bignum_int_compare(const char *left, const char *right);
Sign bignum_int_sanitize(char *num);

Sign bignum_int_addition(const char *addend, const char *aug, char *sum);
Sign bignum_int_subtraction(const char *minuend,
                            const char *subtractor,
                            char *difference);
Sign bignum_int_multiplication(const char *multiplicand,
                               const char *multiplier,
                               char *product);
Sign bignum_int_division(const char *dividend,
                         const char *divisor,
                         char *quotient,
                         char *remainder);

BigNum *bignum_addition(BigNum *addend, BigNum *aug);
BigNum *bignum_subtraction();
BigNum *bignum_multiplication();
BigNum *bignum_division();

#endif /* RETHINK_C_BIGNUM_H */
