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
#include "compare.h"
#include "def.h"
#include "hash.h"
#include "hash_table.h"

#include <stdlib.h>

static inline int huffman_node_compare(HuffmanNode *node1, HuffmanNode *node2)
{
    if (node1->weight < node2->weight) {
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

Heap *huffman_heap_from(const Text *text)
{
    return  huffman_heap_from_string(text_char_string(text), text_length(text));
}

Heap *huffman_heap_from_string(const char *string, unsigned int size)
{
    HashTable *hash_table = hash_table_new(hash_char, char_equal, NULL, free);

    for (unsigned int i = 0; i < size; ++i) {
        unsigned int *count = (unsigned int *)hash_table_get(hash_table, &(string[i]));
        if (count == NULL) {
            // todo: cannot use intdup(1) here, why???
            count = (unsigned int *)malloc(sizeof(unsigned int));
            *count = 1;
            hash_table_insert(hash_table, &(string[i]), count);
        } else {
            ++(*count);
        }
    }

    Heap *heap = huffman_heap_new();
    for (HashTableEntity *iterator = hash_table_first_entity(hash_table);
         iterator != NULL;
         iterator = hash_table_next_entity(hash_table, iterator)) {
        char *key = (char *)iterator->key;
        int *weight = (int *)iterator->value;
        
        huffman_heap_insert(heap, *key, *weight);
    }

    hash_table_free(hash_table);
    return heap;
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

HuffmanTree *huffman_tree_new()
{
    return (HuffmanTree *)malloc(sizeof(HuffmanTree));
}

HuffmanTree *huffman_tree_from(Heap *heap)
{
    HuffmanTree *tree = huffman_tree_new();
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
        heap_insert(heap, node);

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

static inline huffman_node_is_leave(HuffmanNode *node)
{
    return node->left == NULL && node->right == NULL;
}

static void huffman_tree_postorder_to_hash_table(HuffmanNode *node,
                                                 HashTable *hash_table,
                                                 BitMap *bitmap)
{
    if (node == NULL) {
        return;
    }

    if (node->left != NULL) {
        BitMap *left_bitmap = bitmap_clone(bitmap);
        bitmap_append(left_bitmap, 0);
        huffman_tree_postorder_to_hash_table(
            node->left, hash_table, left_bitmap);
    }

    if (node->right != NULL) {
        BitMap *right_bitmap = bitmap_clone(bitmap);
        bitmap_append(right_bitmap, 1);
        huffman_tree_postorder_to_hash_table(
            node->right, hash_table, right_bitmap);
    }

    if (huffman_node_is_leave(node)) {
        // todo: char_dup is not valid here.!!!
        char *ch = (char *)malloc(sizeof(char));
        *ch = node->value;
        hash_table_insert(hash_table, ch, bitmap);
    } else {
        bitmap_free(bitmap);
    }
}

STATIC HashTable *huffman_tree_to_hash_table(HuffmanTree *tree)
{
    /** key: char, value: bitmap */
    HashTable *hash_table =
        hash_table_new(hash_char, char_equal, free, bitmap_free);
    HuffmanNode *node = tree->root;
    BitMap *bitmap = bitmap_new(0);
    huffman_tree_postorder_to_hash_table(tree->root, hash_table, bitmap);
    return hash_table;
}

BitMap *huffman_encode_string(HuffmanTree *tree, const char *string, unsigned int size)
{
    /** key: char, value: bitmap */
    HashTable *hash_table = huffman_tree_to_hash_table(tree);
    BitMap *bitmap = bitmap_new(0);

    for (unsigned int i = 0; i < size; ++i) {
        BitMap *bits = (BitMap *)hash_table_get(hash_table, &(string[i]));
        bitmap_concat(bitmap, bits);
        // todo: error here.
        // for (unsigned int j = 0; j < bits->num_bits; ++j) {
        //     bitmap_append(bitmap, bitmap_get(bits, j));
        // }
    }
    hash_table_free(hash_table);
    return bitmap;
}

BitMap *huffman_encode(HuffmanTree *tree, Text *text)
{
    return  huffman_encode_string(tree, text_char_string(text), text_length(text));
}

Text *huffman_decode(HuffmanTree *tree, BitMap *code)
{
    Text *text = text_new();
    HuffmanNode *node = tree->root;
    for (unsigned int i = 0; i < code->num_bits; ++i) {
        if (bitmap_get(code, i)) {
            node = node->right;
        } else {
            node = node->left;
        }

        if (huffman_node_is_leave(node)) {
            text_append(text, node->value);
            node = tree->root;
        }
    }
    return text;
}

static void huffman_tree_preorder_deflate(HuffmanNode *node, BitMap *bitmap)
{
    if (node == NULL) {
        return;
    }

    if (huffman_node_is_leave(node)) {
        bitmap_append(bitmap, 1);
        bitmap_merge(bitmap, bitmap_from_char(node->value));
    } else {
        bitmap_append(bitmap, 0);
    }

    huffman_tree_preorder_deflate(node->left, bitmap);
    huffman_tree_preorder_deflate(node->right, bitmap);
}

BitMap *huffman_tree_deflate(HuffmanTree *tree)
{
    BitMap *bitmap = bitmap_new(0);
    huffman_tree_preorder_deflate(tree->root, bitmap);
    return bitmap;
}

HuffmanNode *huffman_node_infalte_from_bitmap(BitMap *bitmap, int *index)
{
    HuffmanNode *node;
    int flag = bitmap_get(bitmap, (*index));
    if (flag) {
        ++(*index);
        char ch = bitmap_extract_char(bitmap, (*index));
        (*index) += CHAR_BIT;
        node = huffman_node_new(ch, 0);
    } else {
        ++(*index);
        node = huffman_node_new('\0', 0);

        // left child
        node->left = huffman_node_infalte_from_bitmap(bitmap, index);

        // right child
        node->right = huffman_node_infalte_from_bitmap(bitmap, index);
    }

    return node;
}

HuffmanTree *huffman_tree_inflate(BitMap *bitmap)
{
    HuffmanTree *tree = huffman_tree_new();
    int index = 0;
    tree->root = huffman_node_infalte_from_bitmap(bitmap, &index);
    return tree;
}
