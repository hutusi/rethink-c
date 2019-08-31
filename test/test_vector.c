#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_vector()
{
    Vector *v1 = vector_new(2, 0.0, 1.0);
    ASSERT_INT_EQ(v1->num_dimensions, 2);
    ASSERT_DOUBLE_EQ(v1->coordinates[0], 0, 0.0);
    ASSERT_DOUBLE_EQ(v1->coordinates[1], 1, 0.0);
    vector_free(v1);

    Vector *v2 = vector_new(4, 3.0, 5.0, -3.0, 1.0);
    ASSERT_INT_EQ(v2->num_dimensions, 4);
    ASSERT_DOUBLE_EQ(v2->coordinates[0], 3, 0.0);
    ASSERT_DOUBLE_EQ(v2->coordinates[1], 5, 0.0);
    ASSERT_DOUBLE_EQ(v2->coordinates[2], -3, 0.0);
    ASSERT_DOUBLE_EQ(v2->coordinates[3], 1, 0.0);
    vector_free(v2);

    Vector *v3 = vector_new(0, 3.0, 5.0);
    ASSERT_INT_EQ(v3->num_dimensions, 0);
    vector_free(v3);  
}
