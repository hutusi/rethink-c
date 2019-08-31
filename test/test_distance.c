#include "distance.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_euclidiean_distance()
{
    Vector *v1 = vector_new(2, 0.0, 1.0);
    Vector *v2 = vector_new(2, 3.0, 5.0);
    double distance = euclidiean_distance(v1, v2);
    ASSERT_DOUBLE_EQ(distance, 5.0, 0.0);
    vector_free(v1);
    vector_free(v2);
}

void test_distance()
{
    test_euclidiean_distance();
}
