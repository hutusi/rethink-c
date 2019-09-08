/**
 * @file distance.h
 * @author hutusi (hutusi@outlook.com)
 * @brief 
 * @date 2019-08-29
 * 
 * https://en.wikipedia.org/wiki/Category:Similarity_and_distance_measures
 * 
 * @copyright Copyright (c) 2019, hutusi.com
 * 
 */

#ifndef RETHINK_C_DISTANCE_H
#define RETHINK_C_DISTANCE_H

#include "vector.h"

/**
 * @brief Calculate the Euclidiean distance between two vectors.
 * 
 * @param v1        Vector 1.
 * @param v2        Vector 2.
 * @return double   The Euclidiean distance.
 */
double euclidiean_distance(const Vector *v1, const Vector *v2);

/**
 * @brief Calculate the Manhattan distance (city block) between two vectors.
 * 
 * @param v1            Vector 1.
 * @param v2            Vector 2.
 * @return double       The Manhattan distance.
 */
double manhattan_distance(const Vector *v1, const Vector *v2);

#endif /* #ifndef RETHINK_C_DISTANCE_H */
