#include "huffman.h"
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
    HuffmanTree *tree = huffman_tree_new(heap);

    ASSERT_CHAR_EQ(tree->root->left->value, 'a');
    ASSERT_CHAR_EQ(tree->root->left->weight, 7);
    ASSERT_CHAR_EQ(tree->root->right->weight, 9);
    ASSERT_CHAR_EQ(tree->root->right->left->weight, 4);
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

    HuffmanTree *tree = huffman_tree_new(heap);
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

    HuffmanTree *tree = huffman_tree_new(heap);
    BitMap *code = huffman_encode(tree, text);

    Text *new_text = huffman_decode(tree, code);
    ASSERT_INT_EQ(text_compare(text, new_text), 0);

    bitmap_free(code);
    text_free(new_text);
    text_free(text);
    huffman_tree_free(tree);
}

void test_huffman()
{
    test_huffman_tree();
    test_huffman_encode();
    test_huffman_decode();
}
