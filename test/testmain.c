#include <assert.h>
#include <stdio.h>

#include "alloc-testing.h"

extern void test_arraylist();
extern void test_arraylist_index_of();
extern void test_arraylist_sort();
extern void test_list();
extern void test_list_sort();
extern void test_queue();
extern void test_bitmap();
extern void test_bitmap_words();
extern void test_matrix();
extern void test_matrix_2_dimensions();
extern void test_bstree();
extern void test_bstree_remove();
extern void test_avltree();
extern void test_rbtree();
extern void test_heap();
extern void test_bignum();
extern void test_bignum_int_addition();
extern void test_bignum_int_subtraction();
extern void test_bignum_int_multiplication();
extern void test_bignum_int_division();
extern void test_dijkstra();
extern void test_prime();
extern void test_hash_table();
extern void test_kmp();
extern void test_bm();
extern void test_trie();
extern void test_ac();
extern void test_text();

typedef void (*TestcaseFunc)(void);

static TestcaseFunc all_tests[] = {test_arraylist,
                                   test_arraylist_index_of,
                                   test_arraylist_sort,
                                   test_list,
                                   test_list_sort,
                                   test_queue,
                                   test_bitmap,
                                   test_bitmap_words,
                                   test_matrix,
                                   test_matrix_2_dimensions,
                                   test_bstree,
                                   test_bstree_remove,
                                   test_avltree,
                                   test_rbtree,
                                   test_heap,
                                   test_bignum,
                                   test_bignum_int_addition,
                                   test_bignum_int_subtraction,
                                   test_bignum_int_multiplication,
                                   test_bignum_int_division,
                                   test_dijkstra,
                                   test_prime,
                                   test_hash_table,
                                   test_kmp,
                                   test_bm,
                                   test_trie,
                                   test_ac,
                                   test_text,
                                   NULL};

static void run_test(TestcaseFunc test)
{
    alloc_test_set_limit(-1);
    test();
    assert(alloc_test_get_allocated() == 0);
    printf(".");
}

int main(int argc, char *argv[])
{
    printf("======= Tests[%lu testcases] start ======= \n",
           sizeof(all_tests) / sizeof(TestcaseFunc));

    for (int i = 0; all_tests[i] != NULL; ++i) {
        run_test(all_tests[i]);
    }

    printf("\n======= Tests finished ======= \n");
    return 0;
}
