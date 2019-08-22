/**
 * @file huffman.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to huffman.h
 * @date 2019-08-22
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "huffman.h"
#include "def.h"

static inline int huffman_node_compare(HuffmanNode *node1,
                                        HuffmanNode *node2)
{
    if (node1->weight > node2->weight) {
        return -1;
    } else if (node1->weight > node2->weight) {
        return 1;
    } else {
        return 0;
    }
}

Heap *huffman_heap_new()
{
    return heap_new(MIN_HEAP, huffman_node_compare, free);
}

void huffman_heap_free(Heap *heap)
{
    heap_free(heap);
}

static inline HuffmanNode *huffman_node_new(char value, unsigned int weight)
{
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->value = value;
    node->weight = weight;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int huffman_heap_insert(Heap *heap, char value, unsigned int weight)
{
    HuffmanNode *node = huffman_node_new(value, weight);
    return heap_insert(heap, node);
}

static inline HuffmanNode *huffman_heap_pop(Heap *heap)
{
    return (HuffmanNode *)heap_pop(heap);
}

HuffmanTree *huffman_tree_new(Heap *heap)
{
    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    
    HuffmanNode *node1 = NULL;
    HuffmanNode *node2 = NULL;

    while (1) {
        node1 = huffman_heap_pop(heap);
        node2 = huffman_heap_pop(heap);

        if (node2 == NULL) {
            break;
        }

        unsigned int weight = node1->weight + node2->weight;
        HuffmanNode *node = huffman_node_new('\0', weight);

        if (node1->weight < node2->weight) {
            node->left = node1;
            node->right = node2;
        } else {
            node->left = node2;
            node->right = node1;
        }
    }

    tree->root = node1;

    /** Free heap here: heap is empty now. */
    huffman_heap_free(heap);
    return tree;
}

static void huffman_tree_postorder_free(HuffmanNode *node)
{
    if (node != NULL) {
        huffman_tree_postorder_free(node->left);
        huffman_tree_postorder_free(node->right);
        free(node);
    }
}

void huffman_tree_free(HuffmanTree *tree)
{
    huffman_tree_postorder_free(tree->root);
    free(tree);
}
