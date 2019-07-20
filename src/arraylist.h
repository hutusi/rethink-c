/**
 * @file arraylist.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Automatically resizing array(stack)
 *
 * ArrayLists are arrays of pointers which automatically increase in
 * size.
 *
 * To create an ArrayList, use @ref arraylist_new.
 * To destroy an ArrayList, use @ref arraylist_free.
 *
 * To add a value to an ArrayList, use @ref arraylist_prepend,
 * @ref arraylist_append, or @ref arraylist_insert.
 *
 * To remove a value from an ArrayList, use @ref arraylist_remove
 * or @ref arraylist_remove_range.
 *
 * ArrayList can be treated as stack, use @ref arraylist_push,
 * @ref arraylist_pop to push or pop element value.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_ARRAYLIST_H
#define RETHINK_C_ARRAYLIST_H

/**
 * @brief The type of a value to be stored in an @ref ArrayList.
 *        (void *) can be changed to int, long, or other types if needed.
 */
typedef void *ArrayListValue;

/**
 * @brief Definition of an @ref ArrayList.
 */
typedef struct _ArrayList {
    /** Entries in the array */
    ArrayListValue *data;
    /** Length of the array */
    unsigned int length;
    /** Allocated length of the array.
     * (Private data and should not be accessed) */
    unsigned int _allocated;
} ArrayList;

/**
 * @brief Allocated a new ArrayList for use.
 *
 * @param length            The initiate length of ArrayList.
 * @return ArrayList*
 */
ArrayList *arraylist_new(unsigned int length);

/**
 * @brief Destroy an ArrayList and free back the memory.
 *
 * @param arraylist     The arraylist to free.
 */
void arraylist_free(ArrayList *arraylist);

/**
 * @brief Append a value to the end of an ArrayList.
 *
 * @param arraylist The ArrayList.
 * @param data      The value to append.
 * @return int      0 if success.
 */
int arraylist_append(ArrayList *arraylist, ArrayListValue data);

/**
 * @brief Prepend a value to the beginning of an ArrayList.
 *
 * @param arraylist The ArrayList.
 * @param data      The value to prepend.
 * @return int      0 if success.
 */
int arraylist_prepend(ArrayList *arraylist, ArrayListValue data);

/**
 * @brief Insert a value into an ArrayList.
 *
 * @param arraylist The ArrayList.
 * @param index     The index to be insert.
 * @param data      The value to insert.
 * @return int      0 if success.
 */
int arraylist_insert(ArrayList *arraylist,
                     unsigned int index,
                     ArrayListValue data);

/**
 * @brief Push a value to the end of an ArrayList.
 *
 * @param arraylist The ArrayList.
 * @param data      The value to push.
 * @return int      0 if success.
 */
int arraylist_push(ArrayList *arraylist, ArrayListValue data);

/**
 * @brief Pop a value from the end of an ArrayList.
 *
 * @param arraylist          The ArrayList.
 * @return ArrayListValue    Value if success, otherwise return NULL.
 */
ArrayListValue arraylist_pop(ArrayList *arraylist);

/**
 * @brief Remove the entry at the specified location in an ArrayList.
 *
 * @param arraylist    The ArrayList.
 * @param index        The index of entry to remove.
 * @return int         0 if success.
 */
int arraylist_remove(ArrayList *arraylist, unsigned int index);

/**
 * @brief Remove a range of entries at the specified location in an ArrayList.
 *
 * @param arraylist    The ArrayList.
 * @param index        The index of the start of the range to remove.
 * @param length       The length of the range to remove.
 * @return int         0 if success.
 */
int arraylist_remove_range(ArrayList *arraylist,
                           unsigned int index,
                           unsigned int length);

/**
 * @brief Clear all entries of an ArrayList.
 *
 * @param arraylist    The ArrayList.
 */
void arraylist_clear(ArrayList *arraylist);

/**
 * @brief Compare two values in an ArrayList.
 *
 * @param left     The first value.
 * @param right    The second value.
 * @return         A negative number if left should be sorted before right,
 *                 a positive number if right should be sorted before left,
 *                 zero if the two values are equal.
 */
typedef int (*ArrayListValueCompareFunc)(ArrayListValue left,
                                         ArrayListValue right);

/**
 * @brief Find the index of a particular value in an ArrayList.
 *
 * @param arraylist    The ArrayList.
 * @param callback     The compare function callback.
 * @param data         The value to search for.
 * @return int         The index of the value if found, or -1 if not found.
 */
int arraylist_index_of(ArrayList *arraylist,
                       ArrayListValueCompareFunc callback,
                       ArrayListValue data);

/**
 * @brief Sort the values in an ArrayList.
 *
 * @param arraylist     The ArrayList.
 * @param compare_func  Function callback used to compare values in sorting.
 * @return int          0 if success.
 */
int arraylist_sort(ArrayList *arraylist,
                   ArrayListValueCompareFunc compare_func);

#endif /* #ifndef RETHINK_C_ARRAYLIST_H */
