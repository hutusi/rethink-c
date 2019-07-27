#include "test_helper.h"
#include <stdlib.h>
#include <string.h>
#include "alloc-testing.h"

int int_equal(void *vlocation1, void *vlocation2)
{
    int *location1;
    int *location2;

    location1 = (int *)vlocation1;
    location2 = (int *)vlocation2;

    return *location1 == *location2;
}

int int_compare(void *vlocation1, void *vlocation2)
{
    int *location1;
    int *location2;

    location1 = (int *)vlocation1;
    location2 = (int *)vlocation2;

    if (*location1 < *location2) {
        return -1;
    } else if (*location1 > *location2) {
        return 1;
    } else {
        return 0;
    }
}

int *intdup(int value)
{
    int *dup = (int *)malloc(sizeof(int));
    *dup = value;
    return dup;
}

int string_equal(void *str1, void *str2)
{
    return strcmp((char *)str1, (char *)str2) == 0;
}
