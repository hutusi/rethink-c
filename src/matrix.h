/**
 * @file matrix.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Multi-dimensional Matrix.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_MATRIX_H
#define RETHINK_C_MATRIX_H

/**
 * @brief The type of a value to be stored in a @ref Matrix.
 *        (void *) can be changed to int, long, or other types if needed.
 */
typedef void *MatrixValue;

/**
 * @brief Definition of a @ref Matrix.
 *
 */
typedef struct _Matrix {
    /** Data values in the Matrix. */
    MatrixValue *data;
    /** The total number of data, should equals the multiple product
     *  of all dimensions' length. */
    unsigned int num_data;

    /** The length array of all dimensions. */
    unsigned int *dimensions;
    /** The offsets array of all dimensions.
     *  For example, a 3-dimensional matrix m[3][5][4]:
     *      All 3 dimensions' offsets will be 5*4, 4, 1,
     *      m[2][3][1] will be stored in data[2*5*4 + 3*4 + 1*1].
     */
    unsigned int *offsets;
    /** Numbers of dimensions. */
    unsigned int num_dimensions;
} Matrix;

/**
 * @brief Allcate a new Matrix.
 *
 * @param num_dimensions    The number of dimensions.
 * @param ...               The length of each dimensions.
 * @return Matrix*          The new Matrix if success, otherwise NULL.
 */
Matrix *matrix_new(unsigned int num_dimensions, ...);

/**
 * @brief Delete a Matrix and free back memory.
 *
 * @param matrix    The Matrix to delete.
 */
void matrix_free(Matrix *matrix);

/**
 * @brief Set all entities' value of a Matrix to 0.
 *
 * @param matrix    The Matrix.
 */
void matrix_reset(Matrix *matrix);

/**
 * @brief Set a value to an entity of a Matrix.
 *
 * @param matrix            The Matrix.
 * @param value             The value.
 * @param num_dimensions    The dimensions of the Matrix.
 * @param ...               The index of each dimensions.
 */
void matrix_set(Matrix *matrix,
                MatrixValue value,
                unsigned int num_dimensions,
                ...);

/**
 * @brief Get a value to an entity of a Matrix.
 *
 * @param matrix            The Matrix.
 * @param num_dimensions    The dimensions of the Matrix.
 * @param ...               The index of each dimensions.
 * @return MatrixValue      The value if success.
 */
MatrixValue matrix_get(Matrix *matrix, unsigned int num_dimensions, ...);

#endif /* #ifndef RETHINK_C_MATRIX_H */
