/**
 * @file prime.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to prime.h
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "prime.h"
#include <math.h>

static inline unsigned int bit_map_index_to_number(unsigned int n)
{
    /** from 3: [0] => 3, [1] => 5 */
    return n * 2 + 3;
}

/** para number must be odd number */
static inline unsigned int bit_map_number_to_index(unsigned int number)
{
    /** from 3: [0] => 3, [1] => 5 */
    return (number - 3) / 2;
}

BitMap *prime_number_sieve(unsigned int max_number)
{
    /** prime number should be odd number (except 2),
     * so we only need sieve half of the number.
     * 1 is no need to sieve either.
     */
    unsigned int sieve_size = (max_number - 1) / 2;
    BitMap *sieve = bitmap_new(sieve_size);
    bitmap_set_all(sieve);

    /** only need loop to sqrt(max_number) */
    double max_sqrt = sqrt((double)max_number);
    int max_loop = (unsigned int)ceil(max_sqrt) / 2 + 1;
    for (unsigned int i = 0; i < max_loop; ++i) {
        /** no need to sieve composite's multiples */
        if (!bitmap_get(sieve, i))
            continue;
        unsigned int base_prime = bit_map_index_to_number(i);

        /** each time start from base_prime * base_prime, sieve 3 * 3 first,
         * etc. */
        unsigned int composite = base_prime * base_prime;
        while (composite <= max_number) {
            /** sieve prime */
            unsigned int index = bit_map_number_to_index(composite);
            bitmap_clear(sieve, index);
            composite += (base_prime + base_prime); /** skip even number */
        }
    }

    return sieve;
}
int prime_number_sieve_check(const BitMap *sieve, unsigned int number)
{
    if (number < 2) {
        return 0;
    } else if (number == 2) {
        return 1;
    } else if (number % 2 == 0) {
        return 0;
    } else {
        return bitmap_get(sieve, bit_map_number_to_index(number));
    }
}

unsigned int prime_number_sieve_count(const BitMap *sieve)
{
    return bitmap_count(sieve) + 1; /** plus prime 2 */
}

void prime_number_sieve_free(BitMap *sieve) { bitmap_free(sieve); }
