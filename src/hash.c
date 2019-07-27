/**
 * @file hash.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to hash.h
 * @date 2019-07-26
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "hash.h"

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

unsigned int hash_int(void *pointer)
{
    return *(unsigned int*)pointer;
}

unsigned int hash_object(void *object)
{
    return (unsigned int)object;
}

/**
 * @brief DR hash algorithm.
 * 
 * @param string            Input string.
 * @return unsigned int     Return hash.
 */
unsigned int hash_string(void *string)
{
    unsigned int hash = 0;
    char *p = (char *)string;
    while(*p != '\0') {
        hash = hash * 131 + (*p);
        ++p;
    }
    return hash;
}
