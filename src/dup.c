/**
 * @file dup.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to dup.h
 * @date 2019-08-16
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "dup.h"
#include "def.h"
#include <stdlib.h>

int *intdup(int value)
{
    int *dup = (int *)malloc(sizeof(int));
    *dup = value;
    return dup;
}
