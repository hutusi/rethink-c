#ifndef RETHINK_C_TEST_HELPER_H
#define RETHINK_C_TEST_HELPER_H

int int_equal(void *vlocation1, void *vlocation2);
int int_compare(void *vlocation1, void *vlocation2);

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

int *intdup(int value);
int string_equal(void *str1, void *str2);

#endif /* RETHINK_C_TEST_HELPER_H */
