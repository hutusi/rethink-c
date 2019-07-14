#ifndef RETHINK_C_ARRAYLIST_H
#define RETHINK_C_ARRAYLIST_H

typedef void *ArrayListValue;

typedef struct _ArrayList {
    ArrayListValue *data;
    unsigned int length;
    /* private */
    unsigned int _allocated;
} ArrayList;

ArrayList *arraylist_new(unsigned int length);
void arraylist_free(ArrayList *arraylist);

int arraylist_append(ArrayList *arraylist, ArrayListValue data);
int arraylist_prepend(ArrayList *arraylist, ArrayListValue data);
int arraylist_insert(ArrayList *arraylist,
                     unsigned int index,
                     ArrayListValue data);

int arraylist_remove(ArrayList *arraylist, unsigned int index);
int arraylist_remove_range(ArrayList *arraylist,
                           unsigned int index,
                           unsigned int length);
void arraylist_clear(ArrayList *arraylist);

typedef int (*ArrayListValueCompareFunc)(ArrayListValue left,
                                         ArrayListValue right);
int arraylist_index_of(ArrayList *arraylist,
                       ArrayListValueCompareFunc callback,
                       ArrayListValue data);

int arraylist_sort(ArrayList *arraylist,
                   ArrayListValueCompareFunc compare_func);

#endif /* #ifndef RETHINK_C_ARRAYLIST_H */
