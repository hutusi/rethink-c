/**
 * @file huffman.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Huffman Tree.
 * 
 * todo: 1. store a huffman tree.
 *       2. encode and decode.
 *
 * @date 2019-08-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_HUFFMAN_H
#define RETHINK_C_HUFFMAN_H

#include "heap.h"
#include "bitmap.h"
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
 * @brief Huffman Heap is a Minimum Heap.
 *
 * @return Heap*
 */
Heap *huffman_heap_new();

/**
 * @brief Delete a Huffman Heap and free back memory.
 *
 * Mind: It's unnecessary to free heap manually, free_heap will be called in
 *       huffman_tree_new() function.
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
 * @brief Generate a new Huffman Tree by a Huffman Heap.
 * 
 * @param heap              The Huffman Heap.
 * @return HuffmanTree*     The Huffman Tree.
 */
HuffmanTree *huffman_tree_new(Heap *heap);

/**
 * @brief Delete a Huffman Tree and free back memory.
 * 
 * @param tree      The Huffman Tree.
 */
void huffman_tree_free(HuffmanTree *tree);

BitMap *huffman_encode(HuffmanTree *tree, Text *text);
Text *huffman_decode(HuffmanTree *tree, BitMap *code);

#endif /* #ifndef RETHINK_C_HUFFMAN_H */
