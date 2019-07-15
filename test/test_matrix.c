#include "matrix.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alloc-testing.h"

void test_matrix()
{
    unsigned int width = 3;
    unsigned int height = 5;
    Matrix *matrix = matrix_new(width, height);
    matrix_reset(matrix);

    for (int row; row < matrix->height; ++row) {
        for (int col; col < matrix->width; ++col) {
            assert(matrix_get(matrix, row, col) == 0);
        }
    }

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix_set(matrix, 1, 2, &values[1]);
    assert(int_equal(matrix_get(matrix, 1, 2), &values[1]));
    assert(int_equal(matrix_get(matrix, 1, 2),
                     matrix->data[1 * matrix->width + 2]));

    matrix_set(matrix, 4, 2, &values[2]);
    assert(int_equal(matrix_get(matrix, 4, 2), &values[2]));
    assert(int_equal(matrix_get(matrix, 4, 2),
                     matrix->data[4 * matrix->width + 2]));

    matrix_free(matrix);
}
