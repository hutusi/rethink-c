#include "test_helper.h"
#include <stdlib.h>
#include <string.h>

#include "alloc-testing.h"

#define SWAP(a, b, tmp) tmp=a; a=b; b=tmp;

int string_equal(void *str1, void *str2)
{
    return strcmp((char *)str1, (char *)str2) == 0;
}

int *generate_random_numbers(int from, int to)
{
    int count = to - from + 1;
    int *arr = (int *)malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        arr[i] = i + from;
    }

    int tmp;
    for (int i = 0; i < count; i++) {
        int j = rand()%count;
        SWAP(arr[i], arr[j], tmp);
    }

    return arr;
}
