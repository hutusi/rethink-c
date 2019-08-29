/**
 * @file deflate.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Use Huffman Tree to deflate text file.
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019, hutusi.com
 * 
 */

#include "huffman.h"
#include "hash_table.h"
#include "hash.h"
#include "compare.h"
#include "dup.h"
#include "heap.h"
#include "text.h"
#include "def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text_filename> [<deflate_filename>]", argv[0]);
        return -1;
    }

    char outfile[100];
    outfile[0] = '\0';
    if (argc > 2) {
        strcpy(outfile, argv[2]);
    } else {
        strcpy(outfile, "out.deflate");
    }
    fprintf(stdout, "%s %s ==> %s \n", argv[0], argv[1], outfile);

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error: Cannot open file [%s]", argv[1]);
        return -1;
    }

    fseek(fin, 0, SEEK_END);
    unsigned long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    char *buffer = (char *)malloc(size);
    fread(buffer, 1, size, fin);
    fclose(fin);

    Heap *heap = huffman_heap_from_string(buffer, size);
    HuffmanTree *tree = huffman_tree_from(heap);
    BitMap *textbits = huffman_encode_string(tree, buffer, size);
    BitMap *treebits = huffman_tree_deflate(tree);
    free(buffer);
    huffman_tree_free(tree);

    FILE *fout = fopen(outfile, "w");
    fwrite(&(treebits->num_bits), sizeof(unsigned int), 1, fout);
    fwrite(treebits->words, sizeof(word_t), treebits->num_words, fout);
    fwrite(&(textbits->num_bits), sizeof(unsigned int), 1, fout);
    fwrite(textbits->words, sizeof(word_t), textbits->num_words, fout);
    fclose(fout);

    bitmap_free(treebits);
    bitmap_free(textbits);

    fprintf(stdout, "done! deflate to file [%s]. \n", outfile);

    return 0;
}
