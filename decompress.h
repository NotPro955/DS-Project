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

/* -- Decompress ------------------------------------------------------------ */

static int decompress(const char *input_path, char output_path[50]) {
    /* ALL declarations at the top -- required by C89 */
    FILE          *in;
    FILE          *out;
    HuffNode      *root;
    HuffNode      *node;
    long           freq[256];
    long           total   = 0;
    long           decoded = 0;
    unsigned char  byte    = 0;
    int            bit_pos = 0;
    int            bit;
    int            i;

    in = fopen(input_path, "rb");
    if (!in) { perror("decompress: fopen input"); return 1; }

    /* 1. Read frequency table from header */
    if (fread(freq, sizeof(long), 256, in) != 256) {
        fprintf(stderr, "decompress: bad header\n");
        fclose(in); return 1;
    }

    /* 2. Count total original characters */
    for (i = 0; i < 256; i++) total += freq[i];

    /* 3. Rebuild the Huffman tree */
    root = build_huffman_tree(freq);
    if (!root) { fclose(in); fprintf(stderr, "decompress: empty file\n"); return 1; }

    out = fopen(strcat(output_path,".txt"), "wb");
    if (!out) { perror("decompress: fopen output"); fclose(in); return 1; }

    /* 4. Decode bits by walking the tree */
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