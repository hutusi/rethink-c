#ifndef RETHINK_C_TEST_HELPER_H
#define RETHINK_C_TEST_HELPER_H

#include "compare.h"
#include "dup.h"

#include <math.h>
#include <string.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

#define ASSERT(cond, msg) \
    if (!(cond)) {        \
        printf(msg);      \
        assert(0);        \
    }

#define ASSERT_INT_EQ(a, b)                                           \
    if ((a) != (b)) {                                                 \
        printf("\nassert: Left [%d] not equal to Right[%d]\n", a, b); \
        assert(a == b);                                               \
    }

static inline void assert_double_eq(double a, double b, double tolerance)
{
    if (fabs(a - b) > tolerance) {
        printf("\nassert: Left [%f] not equal to Right[%f] with tolerance "
               "[%f] \n",
               a,
               b,
               tolerance);
        assert(0);
    }
}

#define ASSERT_DOUBLE_EQ assert_double_eq

#define ASSERT_CHAR_EQ(a, b)                                          \
    if ((a) != (b)) {                                                 \
        printf("\nassert: Left [%c] not equal to Right[%c]\n", a, b); \
        assert(a == b);                                               \
    }

#define ASSERT_STRING_EQ(a, b)                                        \
    if (strcmp(a, b) != 0) {                                          \
        printf("\nassert: Left [%s] not equal to Right[%s]\n", a, b); \
        assert(0);                                                    \
    }

#define ASSERT_INT_POINTER_EQ(pointer, value) \
    ASSERT_INT_EQ(*((int *)(pointer)), value)

// inline int *intdup(int value)
// {
//     int *dup = (int *)malloc(sizeof(int));
//     *dup = value;
//     return dup;
// }

// inline int string_equal(void *str1, void *str2)
// {
//     return strcmp((char *)str1, (char *)str2) == 0;
// }

int string_equal(void *str1, void *str2);

#endif /* RETHINK_C_TEST_HELPER_H */
