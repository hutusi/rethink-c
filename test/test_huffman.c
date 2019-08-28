#include "huffman.h"
#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

void test_huffman_tree()
{
    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);

    //                 root
    //              0/       \1
    //             a(7)      (9)
    //                    0/     \1
    //                   (4)      b(5)
    //                 0/   \1
    //               d(1)   c(3)
    HuffmanTree *tree = huffman_tree_from(heap);

    ASSERT_CHAR_EQ(tree->root->left->value, 'a');
    ASSERT_INT_EQ(tree->root->left->weight, 7);
    ASSERT_INT_EQ(tree->root->right->weight, 9);
    ASSERT_INT_EQ(tree->root->right->left->weight, 4);
    ASSERT_CHAR_EQ(tree->root->right->right->value, 'b');
    ASSERT_CHAR_EQ(tree->root->right->left->left->value, 'd');
    ASSERT_CHAR_EQ(tree->root->right->left->right->value, 'c');

    huffman_tree_free(tree);
}

void test_huffman_encode()
{
    Text *text = text_from("abcabcaaaaabbbcd");

    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);

    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *code = huffman_encode(tree, text);

    // a: 0, b: 11, c: 101, d: 100
    // code: 01110101110100000111111101100
    char *bits = bitmap_to_string(code);
    assert(strcmp(bits, "01110101110100000111111101100") == 0);

    free(bits);
    bitmap_free(code);
    text_free(text);
    huffman_tree_free(tree);
}

void test_huffman_decode()
{
    Text *text = text_from("abcabcaaaaabbbcd");

    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);

    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *code = huffman_encode(tree, text);

    //                 root
    //              0/       \1
    //             a(7)      (9)
    //                    0/     \1
    //                   (4)      b(5)
    //                 0/   \1
    //               d(1)   c(3)

    Text *new_text = huffman_decode(tree, code);
    ASSERT_INT_EQ(text_compare(text, new_text), 0);

    bitmap_free(code);
    text_free(new_text);
    text_free(text);
    huffman_tree_free(tree);
}

extern HashTable *huffman_tree_to_hash_table(HuffmanTree *tree);

void test_test_huffman_tree_to_hash_table_bitmap(HashTable *hash_table, char ch, const char *bits)
{
    BitMap *bitmap = (BitMap *)hash_table_get(hash_table, &ch);
    char *str = bitmap_to_string(bitmap);
    ASSERT_STRING_EQ(str, bits);
    // bitmap_free(bitmap);  // cannot free here.
    free(str);
}

void test_huffman_tree_to_hash_table(HuffmanTree *tree)
{
    HashTable *hash_table = huffman_tree_to_hash_table(tree);
    /**
                     root
                  0/       \1
                 a(7)      (12)
                        0/      \1
                       b(5)     b(7)
                              0/    \1
                             c(3)    (4)
                                   0/   \1
                                 d(1)   e(3)
    */
    test_test_huffman_tree_to_hash_table_bitmap(hash_table, 'a', "0");
    test_test_huffman_tree_to_hash_table_bitmap(hash_table, 'b', "10");
    test_test_huffman_tree_to_hash_table_bitmap(hash_table, 'c', "110");
    test_test_huffman_tree_to_hash_table_bitmap(hash_table, 'd', "1110");
    test_test_huffman_tree_to_hash_table_bitmap(hash_table, 'e', "1111");

    hash_table_free(hash_table);
}

void test_huffman_decode_same_weight()
{
    Text *text = text_from("abcabcaaaaabbbcdeee");

    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);
    huffman_heap_insert(heap, 'e', 3);

    HuffmanTree *tree = huffman_tree_from(heap);

    /**
                     root
                  0/       \1
                 a(7)      (12)
                        0/      \1
                       b(5)     b(7)
                              0/    \1
                             c(3)    (4)
                                   0/   \1
                                 d(1)   e(3)
    */

    ASSERT_CHAR_EQ(tree->root->left->value, 'a');
    ASSERT_CHAR_EQ(tree->root->right->left->value, 'b');
    ASSERT_CHAR_EQ(tree->root->right->right->left->value, 'c');
    ASSERT_CHAR_EQ(tree->root->right->right->right->left->value, 'd');
    ASSERT_CHAR_EQ(tree->root->right->right->right->right->value, 'e');

    /** test */
    test_huffman_tree_to_hash_table(tree);

    BitMap *code = huffman_encode(tree, text);

    Text *new_text = huffman_decode(tree, code);
    ASSERT_INT_EQ(text_compare(text, new_text), 0);

    bitmap_free(code);
    text_free(new_text);
    text_free(text);
    huffman_tree_free(tree);
}

void test_huffman_encode_long_text()
{
    Text *text = text_from(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus mollis massa magna, non pellentesque odio pretium tempor. Nam faucibus euismod eleifend. Curabitur libero odio, dignissim et velit eleifend, rhoncus porta sapien. Curabitur dictum turpis elit, id pellentesque orci sagittis in. Fusce cursus, velit vitae porta ornare, felis lorem congue libero, vel fringilla turpis ex in nisl. Fusce consequat sit amet lorem sed rhoncus. Donec nec iaculis felis. Proin at finibus neque. Aliquam egestas venenatis ante, vitae euismod mauris congue eget. Morbi risus nulla, efficitur vehicula ultricies id, commodo ac diam. In a leo efficitur, lobortis libero et, luctus orci. Donec eu nisi vitae leo gravida tempor eget vel orci. Vestibulum congue, orci nec aliquam mollis, lorem eros eleifend arcu, condimentum tempor est orci quis odio. Integer suscipit magna a tortor finibus interdum. Mauris sodales pretium metus, ut feugiat leo pellentesque in. Praesent vel ipsum porta, ultricies dolor ornare, commodo nulla.\
\
Maecenas consectetur neque ut dapibus dignissim. Nunc imperdiet vel dolor at placerat. Suspendisse mattis gravida consequat. Quisque semper vel ligula in suscipit. Nam faucibus eget purus ac lobortis. Suspendisse eleifend semper ultrices. Integer pellentesque vel est at feugiat. Mauris sit amet luctus enim, ac aliquet orci. Curabitur nisl metus, fermentum quis consectetur non, sodales vulputate felis. Ut sit amet vehicula leo, eu luctus dui.\
\
Fusce vitae libero sit amet lectus rutrum vestibulum. Nunc sit amet sem quis sem facilisis interdum. Mauris pretium pellentesque leo consequat dictum. Vivamus congue elit a tellus facilisis, sit amet semper neque posuere. Ut nunc ipsum, elementum quis magna ut, fringilla facilisis massa. Nam ac feugiat felis, eget iaculis odio. Vivamus porttitor mi suscipit mi aliquet aliquam. Maecenas quis quam vitae eros rutrum euismod. Suspendisse sapien ligula, consequat vel scelerisque dapibus, fermentum eget justo. Aliquam sit amet felis non sem ornare semper. Nunc neque est, bibendum et tempor ac, feugiat ac nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Maecenas consectetur vulputate sem eu ultricies.\
\
Donec est quam, consequat in pretium ac, varius vitae turpis. Pellentesque blandit tincidunt luctus. Nulla blandit tristique justo, at feugiat nulla interdum nec. Aenean sit amet eros velit. Etiam sed cursus nibh. Donec est tellus, accumsan et cursus nec, consequat nec augue. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur ac iaculis elit. Donec suscipit magna tortor, quis maximus turpis laoreet eu. Curabitur enim risus, efficitur a enim non, mollis tristique nisi. Sed nec tellus libero. Morbi varius vel metus quis vulputate. Donec porta purus elit, a condimentum arcu consectetur ut. Duis aliquam commodo nibh consequat volutpat. Nulla bibendum augue id sem interdum tristique.\
\
Ut non eros commodo, hendrerit dui ac, lobortis lacus. Phasellus ac lacus gravida, sollicitudin lacus eleifend, dictum massa. Etiam viverra lectus a tempus efficitur. Vestibulum sit amet velit elit. Nulla vestibulum egestas pellentesque. Nullam ac egestas lacus. Curabitur lectus arcu, auctor ac malesuada vitae, dignissim sit amet purus. Donec eros mauris, fermentum vitae cursus non, aliquam ac sapien. Fusce semper sapien massa, quis placerat tellus semper eu. Sed viverra nunc non diam sagittis bibendum. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Morbi augue odio, aliquet vel semper vel, suscipit eget justo. In vehicula turpis vitae erat viverra varius. Curabitur molestie quam nec nulla ornare, sit amet egestas nisl facilisis. Nullam ultricies fermentum ante bibendum faucibus.");

    Heap *heap = huffman_heap_from(text);

    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *code = huffman_encode(tree, text);

    Text *new_text = huffman_decode(tree, code);
    ASSERT_INT_EQ(text_compare(text, new_text), 0);

    bitmap_free(code);
    text_free(new_text);
    text_free(text);
    huffman_tree_free(tree);
}

void test_huffman_tree_deflate()
{
    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);

    //                 root
    //              0/       \1
    //             a(7)      (9)
    //                    0/     \1
    //                   (4)      b(5)
    //                 0/   \1
    //               d(1)   c(3)

    // will be stored as:

    //   01a001d1c1b
    BitMap *expected = bitmap_new(0);
    bitmap_append(expected, 0);
    bitmap_append(expected, 1);
    bitmap_append_char(expected, 'a');
    bitmap_append(expected, 0);
    bitmap_append(expected, 0);
    bitmap_append(expected, 1);
    bitmap_append_char(expected, 'd');
    bitmap_append(expected, 1);
    bitmap_append_char(expected, 'c');
    bitmap_append(expected, 1);
    bitmap_append_char(expected, 'b');

    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *bitmap = huffman_tree_deflate(tree);
    // HuffmanTree *deflate_tree = huffman_tree_inflate(heap);

    ASSERT(bitmap_equal(bitmap, expected),
           "Huffman tree deflate bitmap not euqal to expected.");

    bitmap_free(bitmap);
    bitmap_free(expected);
    // huffman_tree_free(deflate_tree);
    huffman_tree_free(tree);
}

void test_huffman_tree_inflate()
{
    Heap *heap = huffman_heap_new();
    huffman_heap_insert(heap, 'a', 7);
    huffman_heap_insert(heap, 'b', 5);
    huffman_heap_insert(heap, 'c', 3);
    huffman_heap_insert(heap, 'd', 1);

    //                 root
    //              0/       \1
    //             a(7)      (9)
    //                    0/     \1
    //                   (4)      b(5)
    //                 0/   \1
    //               d(1)   c(3)

    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *bitmap = huffman_tree_deflate(tree);

    // tree will be deflated as:
    //   01a001d1c1b

    HuffmanTree *deflate_tree = huffman_tree_inflate(bitmap);

    /***********************************************
     *                  0
     *                 root
     *              1/       \0
     *             a(7)      (9)
     *                    0/     \1
     *                   (4)      b(5)
     *                 1/   \1
     *               d(1)   c(3)
     ************************************************/

    ASSERT_CHAR_EQ(deflate_tree->root->left->value, 'a');
    ASSERT_INT_EQ(deflate_tree->root->left->weight, 0);
    ASSERT_CHAR_EQ(deflate_tree->root->right->right->value, 'b');
    ASSERT_CHAR_EQ(deflate_tree->root->right->left->left->value, 'd');
    ASSERT_CHAR_EQ(deflate_tree->root->right->left->right->value, 'c');

    bitmap_free(bitmap);
    huffman_tree_free(deflate_tree);
    huffman_tree_free(tree);
}

void test_huffman()
{
    test_huffman_tree();
    test_huffman_encode();
    test_huffman_encode();
    test_huffman_decode();
    test_huffman_decode_same_weight();
    test_huffman_encode_long_text();
    test_huffman_tree_deflate();
    test_huffman_tree_inflate();
}
