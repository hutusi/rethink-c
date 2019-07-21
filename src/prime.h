/**
 * @file prime.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Prime number calculation.
 *
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_PRIME_H
#define RETHINK_C_PRIME_H

#include "bitmap.h"

/**
 * @brief Sieve the prime numbers less than or equal to specific max number.
 *
 * @param max_number    The max number.
 * @return BitMap*      The sieve bitmap.
 */
BitMap *prime_number_sieve(unsigned int max_number);

/**
 * @brief Check if a number is prime number.
 *
 * Need call prime_number_sieve to get the sieve bitmap first.
 *
 * @param sieve     The prime sieve bitmap.
 * @param number    The number.
 * @return int      1 if prime, otherwise 0.
 */
int prime_number_sieve_check(const BitMap *sieve, unsigned int number);

/**
 * @brief Count the amount of all prime numbers in a prime sieve.
 *
 * @param sieve             The sieve.
 * @return unsigned int     The amount.
 */
unsigned int prime_number_sieve_count(const BitMap *sieve);

/**
 * @brief Delete a prime sieve and free back memory.
 *
 * @param sieve     The prime sieve.
 */
void prime_number_sieve_free(BitMap *sieve);

#endif /* #ifndef RETHINK_C_PRIME_H */
