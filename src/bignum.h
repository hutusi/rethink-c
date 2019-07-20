/**
 * @file bignum.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Big number operation: Addition, Subtraction, Multiplication,
 *        and Division. Use char string to store big number.
 *
 * Before arithmetic calculations, use @ref bignum_int_sanitize to
 * sanitize the char string.
 *
 * To do addition, use @ref bignum_int_addition.
 *
 * To do subtraction, use @ref bignum_int_subtraction.
 *
 * To do multiplication, use @ref bignum_int_multiplication.
 *
 * To do division, use @ref bignum_int_division.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_BIGNUM_H
#define RETHINK_C_BIGNUM_H

/**
 * @brief The sign type to differentiate positive or negative number.
 *        NaN means Not a Number.
 */
typedef enum _Sign { Positive = 1, Negative = -1, NaN = 0 } Sign;

/**
 * @brief Compare an number with zero.
 *
 * @param num    the Number.
 * @return int   1 if greater than 0, -1 if less than 0, 0 if equals 0.
 */
int bignum_int_compare_zero(const char *num);

/**
 * @brief Compare two number.
 *
 * @param left   The first number.
 * @param right  The second number.
 * @return int   1 if left greater than right, -1 if right greater than left,
 *               0 if left equals right.
 */
int bignum_int_compare(const char *left, const char *right);

/**
 * @brief Sanitize the number(char string).
 *
 * For the big number is represented as char string, it should be sanitized
 * before do calculations. e.g., "0001 " "0001" "-123456" will delete 0s or
 * blanks, and the sign '+' or '-' will be deleted too, return the sign.
 *
 * @param num    The number be both input and output para. If the input number
 *               is a invalid number string (like "ABC001"), it will be output
 *               as "0".
 * @return Sign  The number's sign.
 */
Sign bignum_int_sanitize(char *num);

/**
 * @brief Do addition.
 *
 * @param addend  The addend number.
 * @param aug     The augend number.
 * @param sum     The sum.
 * @return Sign   The sum sign. (Always Positive.)
 */
Sign bignum_int_addition(const char *addend, const char *aug, char *sum);

/**
 * @brief Do subtraction.
 *
 * @param minuend       The minuend number.
 * @param subtractor    The subtractor number.
 * @param difference    The difference number.
 * @return Sign         The difference sign.
 */
Sign bignum_int_subtraction(const char *minuend,
                            const char *subtractor,
                            char *difference);

/**
 * @brief Do multiplication.
 *
 * @param multiplicand  The multiplicand number.
 * @param multiplier    The multiplier number.
 * @param product       The product number.
 * @return Sign         The product sign. (Always Positive.)
 */
Sign bignum_int_multiplication(const char *multiplicand,
                               const char *multiplier,
                               char *product);

/**
 * @brief Do division.
 *
 * @param dividend      The dividend number.
 * @param divisor       The divisor number.
 * @param quotient      The quotient number.
 * @param remainder     The remainder number.
 * @return Sign         The product sign. (Always Positive.)
 */
Sign bignum_int_division(const char *dividend,
                         const char *divisor,
                         char *quotient,
                         char *remainder);

#endif /* RETHINK_C_BIGNUM_H */
