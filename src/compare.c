/**
 * @file compare.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to compare.h
 * @date 2019-08-11
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "compare.h"
#include "def.h"

int int_equal(void *address1, void *address2)
{
    return *((int *)address1) == *((int *)address2);
}

int int_compare(void *address1, void *address2)
{
    int value1 = *((int *)address1);
    int value2 = *((int *)address2);

    if (value1 < value2) {
        return -1;
    } else if (value1 > value2) {
        return 1;
    } else {
        return 0;
    }
}

int char_equal(void *address1, void *address2)
{
    return *((char *)address1) == *((char *)address2);
}

int char_compare(void *address1, void *address2)
{
    char value1 = *((char *)address1);
    char value2 = *((char *)address2);

    if (value1 < value2) {
        return -1;
    } else if (value1 > value2) {
        return 1;
    } else {
        return 0;
    }
}
