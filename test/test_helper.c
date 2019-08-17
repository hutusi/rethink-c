#include "test_helper.h"
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"

int string_equal(void *str1, void *str2)
{
    return strcmp((char *)str1, (char *)str2) == 0;
}
