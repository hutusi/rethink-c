/**
 * @file vector.c
 * @author hutusi (hutusi@outlook.com)
 * @brief 
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019, hutusi.com
 * 
 */

#include "vector.h"
#include "def.h"
#include <stdarg.h>
#include <stdlib.h>

Vector *vector_new(unsigned int num_dimensions, ...)
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    if (vector == NULL) {
        return NULL;
    }
    vector->num_dimensions = num_dimensions;
    vector->coordinates = (double *)malloc(sizeof(double) * num_dimensions);
    if (vector->coordinates == NULL) {
        free(vector);
        return NULL;
    }

    va_list vl;
    va_start(vl, num_dimensions);
    for (int i = 0; i < num_dimensions; ++i) {
        vector->coordinates[i] = va_arg(vl, double);
    }
    va_end(vl);

    return vector;
}

void vector_free(Vector *vector)
{
    free(vector->coordinates);
    free(vector);
}
