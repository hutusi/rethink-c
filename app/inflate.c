/**
 * @file inflate.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Use Huffman Tree to inflate binary file to Text file.
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
        fprintf(stderr, "Usage: %s <text_filename> [<inflate_filename>]", argv[0]);
        return -1;
    }

    char outfile[100];
    outfile[0] = '\0';
    if (argc > 2) {
        strcpy(outfile, argv[2]);
    } else {
        strcpy(outfile, "out.txt");
    }
    fprintf(stdout, "%s %s ==> %s \n", argv[0], argv[1], outfile);

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error: Cannot open file [%s]", argv[1]);
        return -1;
    }

    /** [tree_size][tree_bits][encode_size][encode_bits]*/
    unsigned int num_bits;
    fread(&num_bits, sizeof(unsigned int), 1, fin);
    BitMap *treebits = bitmap_new(num_bits);
    fread(treebits->words, sizeof(word_t), treebits->num_words, fin);

    fread(&num_bits, sizeof(unsigned int), 1, fin);
    BitMap *textbits = bitmap_new(num_bits);
    fread(textbits->words, sizeof(word_t), textbits->num_words, fin);

    fclose(fin);

    HuffmanTree *tree = huffman_tree_inflate(treebits);
    Text *text = huffman_decode(tree, textbits);
    bitmap_free(treebits);
    bitmap_free(textbits);
    huffman_tree_free(tree);

    FILE *fout = fopen(outfile, "w");
    fwrite(text_char_string(text), sizeof(char), text_length(text), fout);
    fclose(fout);
    text_free(text);

    fprintf(stdout, "done! inflate to file [%s]. \n", outfile);

    return 0;
}
