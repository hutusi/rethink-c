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
#include <stdlib.h>
#include "def.h"

int *intdup(int value)
{
    int *dup = (int *)malloc(sizeof(int));
    *dup = value;
    return dup;
}

char *char_dup(char value)
{
    char *dup = (char *)malloc(sizeof(char));
    *dup = value;
    return dup;
}
