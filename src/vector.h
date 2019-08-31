/**
 * @file vector.h
 * @author hutusi (hutusi@outlook.com)
 * @brief Vector.
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019, hutusi.com
 * 
 */

#ifndef RETHINK_C_VECTOR_H
#define RETHINK_C_VECTOR_H

/**
 * @brief Definition of a @ref Vector.
 * 
 */
typedef struct _Vector {
    double *coordinates;
    unsigned int num_dimensions;
} Vector;

/**
 * @brief Malloc a new Vector.
 * 
 * @param num_dimensions 
 * @param ...               The coordinates, should be double. e.g., 1.0, not 1.
 * @return Vector*          The new Vector.
 */
Vector *vector_new(unsigned int num_dimensions, ...);

/**
 * @brief Delete a Vector and free back memory.
 * 
 * @param vector    The Vector to delete.
 */
void vector_free(Vector *vector);

#endif /* #ifndef RETHINK_C_VECTOR_H */
