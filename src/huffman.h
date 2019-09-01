/**
 * @file huffman.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Huffman Tree.
 *
 * Use huffman_tree_from to generate a new Huffman Tree from a Minimum HEAP.
 *
 * Use huffman_encode or huffman_decode to encode or decode Text.
 *
 * Use huffman_tree_deflate or huffman_tree_inflate to store or restor itself.
 *
 * @date 2019-08-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_HUFFMAN_H
#define RETHINK_C_HUFFMAN_H

#include "bitmap.h"
#include "heap.h"
#include "text.h"

/**
 * @brief Definition of a @ref HuffmanNode.
 *
 */
typedef struct _HuffmanNode {
    char value;
    unsigned int weight;
    struct _HuffmanNode *left;
    struct _HuffmanNode *right;
} HuffmanNode;

/**
 * @brief Definition of a @ref HuffmanTree.
 *
 */
typedef struct _HuffmanTree {
    HuffmanNode *root;
} HuffmanTree;

/**
 * @brief Malloc a new Huffman Heap.
 *
 * Huffman Heap is a Minimum Heap.
 *
 * @return Heap*    The Huffman Heap.
 */
Heap *huffman_heap_new();

/**
 * @brief Generate a new Huffman Heap from a Text.
 *
 * @param text      The Text.
 * @return Heap*    The Huffman Heap.
 */
Heap *huffman_heap_from(const Text *text);

/**
 * @brief Generate a new Huffman Heap from a string.
 *
 * @param string    The string.
 * @param size      The size of the string.
 * @return Heap*    The Huffman Heap.
 */
Heap *huffman_heap_from_string(const char *string, unsigned int size);

/**
 * @brief Delete a Huffman Heap and free back memory.
 *
 * Mind: It's unnecessary to free heap manually, free_heap will be called in
 *       huffman_tree_from(heap) function.
 *
 * @param heap  The Huffman Heap.
 */
void huffman_heap_free(Heap *heap);

/**
 * @brief Insert a value and it's weight to a Huffman Heap.
 *
 * @param tree      The heap.
 * @param value     The value.
 * @param weight    The weight.
 * @return int      0 if success.
 */
int huffman_heap_insert(Heap *heap, char value, unsigned int weight);

/**
 * @brief Allocate a new Huffman Tree.
 *
 * @return HuffmanTree*     The new Huffman Tree.
 */
HuffmanTree *huffman_tree_new();

/**
 * @brief Generate a new Huffman Tree by a Huffman Heap.
 *
 * Mind: this function will free the input heap.
 *
 * @param heap              The Huffman Heap.
 * @return HuffmanTree*     The Huffman Tree.
 */
HuffmanTree *huffman_tree_from(Heap *heap);

/**
 * @brief Delete a Huffman Tree and free back memory.
 *
 * @param tree      The Huffman Tree.
 */
void huffman_tree_free(HuffmanTree *tree);

/**
 * @brief Encode a Text to a sequence of BitMap by a Huffman Tree coding.
 *
 * @param tree      The Huffman Tree coding.
 * @param text      The Text.
 * @return BitMap*  The BitMap.
 */
BitMap *huffman_encode(const HuffmanTree *tree, const Text *text);

/**
 * @brief Encode a string to a sequence of BitMap by a Huffman Tree coding.
 *
 * @param tree      The Huffman Tree coding.
 * @param string    The string.
 * @param size      The size of the string.
 * @return BitMap*  The BitMap.
 */
BitMap *huffman_encode_string(const HuffmanTree *tree,
                              const char *string,
                              unsigned int size);

/**
 * @brief Decode a sequence of BitMap to a Text by a Huffman Tree coding.
 *
 * @param tree      The Huffman Tree coding.
 * @param bitmap    The BitMap.
 * @return Text*    The Text.
 */
Text *huffman_decode(const HuffmanTree *tree, const BitMap *bitmap);

/**
 * @brief Deflate a Huffman Tree to a BitMap for storing with few storage.
 *
 * @param tree      The Huffman Tree.
 * @return BitMap*  The BitMap.
 */
BitMap *huffman_tree_deflate(const HuffmanTree *tree);

/**
 * @brief Inflate a BitMap to a Huffman Tree. (Restore.)
 *
 * @param bitmap            The BitMap.
 * @return HuffmanTree*     The Huffman Tree.
 */
HuffmanTree *huffman_tree_inflate(const BitMap *bitmap);

/**
 * @brief Judge two Huffman Tree's equality.
 *
 * @param tree1     One Huffman Tree.
 * @param tree2     The other Huffman Tree.
 * @return int      1 if equal, 0 if not.
 */
int huffman_tree_equal(const HuffmanTree *tree1, const HuffmanTree *tree2);

#endif /* #ifndef RETHINK_C_HUFFMAN_H */
