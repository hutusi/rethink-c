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
 * @param v1        One vector.
 * @param v2        Another vector.
 * @return double   The Euclidiean distance.
 */
double euclidiean_distance(const Vector *v1, const Vector *v2);

#endif /* #ifndef RETHINK_C_DISTANCE_H */
