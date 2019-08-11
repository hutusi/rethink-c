#include "prime.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_prime_1()
{
    BitMap *sieve = prime_number_sieve(100);

    assert(prime_number_sieve_check(sieve, 2));
    assert(prime_number_sieve_check(sieve, 3));
    assert(prime_number_sieve_check(sieve, 11));

    assert(prime_number_sieve_check(sieve, 83));
    assert(prime_number_sieve_check(sieve, 89));
    assert(prime_number_sieve_check(sieve, 97));

    assert(!prime_number_sieve_check(sieve, 88));
    assert(!prime_number_sieve_check(sieve, 99));
    assert(!prime_number_sieve_check(sieve, 81));

    assert(!prime_number_sieve_check(sieve, 1));
    assert(!prime_number_sieve_check(sieve, 0));

    prime_number_sieve_free(sieve);
}

void test_prime_2()
{
    /** 1 billion, take long time. */
    // BitMap *sieve = prime_number_sieve(1000000000);
    // unsigned int count = prime_number_sieve_count(sieve);
    // printf("Prime numbers count: ==%u==", count);
    // assert(count == 50847534);
    // prime_number_sieve_free(sieve);
}

void test_prime_3()
{
    /** 1 million. */
    BitMap *sieve = prime_number_sieve(1000000);
    unsigned int count = prime_number_sieve_count(sieve);
    // printf("Prime numbers count: ==%u==", count);
    assert(count == 78498);
    prime_number_sieve_free(sieve);
}

void test_prime()
{
    test_prime_1();
    test_prime_2();
    test_prime_3();
}
