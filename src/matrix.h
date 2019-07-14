#ifndef RETHINK_C_MATRIX_H
#define RETHINK_C_MATRIX_H

typedef void *MatrixValue;

typedef struct _Matrix {
    MatrixValue *data;
    unsigned int width;
    unsigned int height;
} Matrix;

Matrix *matrix_new(unsigned int width, unsigned int height);
void matrix_free(Matrix *matrix);
void matrix_reset(Matrix *matrix);

void matrix_set(Matrix *matrix,
                unsigned int row,
                unsigned int col,
                MatrixValue value);
MatrixValue matrix_get(Matrix *matrix, unsigned int row, unsigned int col);

#endif /* #ifndef RETHINK_C_MATRIX_H */
