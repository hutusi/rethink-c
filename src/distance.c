#include "distance.h"
#include <math.h>

/**
 *        v1
 *          \
 *           \   <------ Euclidiean distance
 *            \
 *             v2
 * 
 */
double euclidiean_distance(const Vector *v1, const Vector *v2)
{
    double amount = 0;
    for (int i = 0; i < v1->num_dimensions; ++i) {
        double distance = fabs(v2->coordinates[i] - v1->coordinates[i]);
        amount += distance * distance;
    }

    return sqrt(amount);
}

/**
 *         v1
 *          |
 *           -         <------ Manhattan distance (city block)
 *            |
 *             -----v2
 */
double manhattan_distance(const Vector *v1, const Vector *v2)
{
    double distance = 0;
    for (int i = 0; i < v1->num_dimensions; ++i) {
        distance += fabs(v2->coordinates[i] - v1->coordinates[i]);
    }

    return distance;
}
