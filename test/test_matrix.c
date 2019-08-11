#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_matrix() {}

void test_matrix_2_dimensions()
{
    unsigned int dimensions = 2;
    unsigned int width = 3;
    unsigned int height = 5;
    Matrix *matrix = matrix_new(dimensions, height, width);
    matrix_reset(matrix);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            assert(matrix_get(matrix, dimensions, row, col) == 0);
        }
    }

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix_set(matrix, &values[1], dimensions, 1, 2);
    assert(int_equal(matrix_get(matrix, dimensions, 1, 2), &values[1]));
    assert(int_equal(matrix_get(matrix, dimensions, 1, 2),
                     matrix->data[1 * width + 2]));

    matrix_set(matrix, &values[2], dimensions, 4, 2);
    assert(int_equal(matrix_get(matrix, dimensions, 4, 2), &values[2]));
    assert(int_equal(matrix_get(matrix, dimensions, 4, 2),
                     matrix->data[4 * width + 2]));

    matrix_free(matrix);
}
