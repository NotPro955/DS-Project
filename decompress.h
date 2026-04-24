// Raghav
// TODO:
// Reverse the compression
// Will let you know the details soon
#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include <stdio.h>
#include "huffman.h"

/* -- Bit reader ------------------------------------------------------------ */
static int read_bit(FILE *f, unsigned char *byte, int *bit_pos) {
    int bit;
    if (*bit_pos == 0) {
        if (fread(byte, 1, 1, f) != 1) return -1;
    }
    bit      = (*byte >> (7 - *bit_pos)) & 1;
    *bit_pos = (*bit_pos + 1) % 8;
    return bit;
}

/* -- Tree deserialiser -----------------------------------------------------
   Mirrors write_tree in compress.h:
     Read 1 bit: 1 = leaf (read 8-bit symbol), 0 = internal (recurse L+R)
--------------------------------------------------------------------------- */
static HuffNode *read_tree(FILE *f, unsigned char *byte, int *bit_pos) {
    int bit = read_bit(f, byte, bit_pos);
    if (bit == -1) return NULL;

    if (bit == 1) {
        /* Leaf: read 8-bit symbol */
        int ch = 0, i;
        for (i = 7; i >= 0; i--) {
            int b = read_bit(f, byte, bit_pos);
            if (b == -1) return NULL;
            ch |= (b << i);
        }
        return huff_new_node(ch, 0);
    } else {
        /* Internal node */
        HuffNode *node  = huff_new_node(-1, 0);
        node->left      = read_tree(f, byte, bit_pos);
        node->right     = read_tree(f, byte, bit_pos);
        return node;
    }
}

/* -- Decompress ------------------------------------------------------------ */
static int decompress(const char *input_path, char output_path[50]) {
    /* ALL declarations at the top -- required by C89 */
    FILE          *in;
    FILE          *out;
    HuffNode      *root;
    HuffNode      *node;
    unsigned int   total   = 0;
    unsigned int   decoded = 0;
    unsigned char  byte    = 0;
    int            bit_pos = 0;
    int            bit;

    in = fopen(input_path, "rb");
    if (!in) { perror("decompress: fopen input"); return 1; }

    /* 1. Read total character count (4 bytes) */
    if (fread(&total, sizeof(unsigned int), 1, in) != 1) {
        fprintf(stderr, "decompress: bad header\n");
        fclose(in); return 1;
    }

    /* 2. Reconstruct the Huffman tree from bit-packed pre-order data */
    root = read_tree(in, &byte, &bit_pos);
    if (!root) { fclose(in); fprintf(stderr, "decompress: bad tree\n"); return 1; }

    out = fopen(strcat(output_path, ".txt"), "wb");
    if (!out) { perror("decompress: fopen output"); fclose(in); return 1; }

    /* 3. Decode bits by walking the tree */
    node = root;
    while (decoded < total) {
        bit = read_bit(in, &byte, &bit_pos);
        if (bit == -1) break;

        node = bit ? node->right : node->left;
        if (!node) break;

        if (node->ch != -1) {
            fputc(node->ch, out);
            node = root;
            decoded++;
        }
    }

    fclose(in);
    fclose(out);
    free_tree(root);
    return 0;
}

#endif /* DECOMPRESSION_H */