/**
 * @file matrix.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to matrix.h
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "matrix.h"
#include "def.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

Matrix *matrix_new(unsigned int num_dimensions, ...)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->dimensions =
        (unsigned int *)malloc(sizeof(unsigned int) * num_dimensions);

    matrix->num_dimensions = num_dimensions;

    /** todo: ensure matrix->num_data should not greater than MAX_UINT! */
    matrix->num_data = 1;

    va_list vl;
    va_start(vl, num_dimensions);
    for (int i = 0; i < num_dimensions; ++i) {
        matrix->dimensions[i] = va_arg(vl, unsigned int);
        matrix->num_data *= matrix->dimensions[i];
    }
    va_end(vl);

    matrix->offsets =
        (unsigned int *)malloc(sizeof(unsigned int) * num_dimensions);
    unsigned int offsets = 1; // the last dimension offset * 1
    for (int i = num_dimensions - 1; i >= 0; --i) {
        matrix->offsets[i] = offsets;
        offsets *= matrix->dimensions[i];
    }

    matrix->data =
        (MatrixValue *)malloc(sizeof(MatrixValue) * matrix->num_data);
    if (matrix->data == NULL) {
        free(matrix->dimensions);
        free(matrix->offsets);
        free(matrix);
        return NULL;
    }

    return matrix;
}

void matrix_free(Matrix *matrix)
{
    free(matrix->dimensions);
    free(matrix->offsets);
    free(matrix->data);
    free(matrix);
}

void matrix_reset(Matrix *matrix)
{
    memset(matrix->data, 0, matrix->num_data * sizeof(MatrixValue));
}

void matrix_set(Matrix *matrix,
                MatrixValue value,
                unsigned int num_dimensions,
                ...)
{
    unsigned int offset = 0;

    va_list vl;
    va_start(vl, num_dimensions);
    for (int i = 0; i < num_dimensions; ++i) {
        unsigned demension_index = va_arg(vl, unsigned int);
        offset += demension_index * matrix->offsets[i];
    }
    va_end(vl);

    matrix->data[offset] = value;
}

MatrixValue matrix_get(Matrix *matrix, unsigned int num_dimensions, ...)
{
    unsigned int offset = 0;

    va_list vl;
    va_start(vl, num_dimensions);
    for (int i = 0; i < num_dimensions; ++i) {
        unsigned demension_index = va_arg(vl, unsigned int);
        offset += demension_index * matrix->offsets[i];
    }
    va_end(vl);

    return matrix->data[offset];
}
