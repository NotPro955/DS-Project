// Mukesh
// Todo:
// convert the text into binary based on recieved data
// left -0 and right -1
#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include "freq.h"
#include "huffman.h"

/* -- Bit writer ------------------------------------------------------------ */
void write_bit(FILE *f, unsigned char *byte, int *bit_pos, int bit) {
    if (bit) *byte |= (1 << (7 - *bit_pos));
    (*bit_pos)++;
    if (*bit_pos == 8) {
        fwrite(byte, 1, 1, f);
        *byte    = 0;
        *bit_pos = 0;
    }
}

/* -- Tree serialiser (pre-order, bit-packed) --------------------------------
   Format per node:
     Internal node : bit 0, then recurse left then right
     Leaf node     : bit 1, then 8 bits of symbol value
   For N unique symbols the tree costs (2N-1) + 8N = 10N-1 bits.
   24 unique chars -> ceil(239/8) = 30 bytes  vs  24*5+2 = 122 bytes sparse.
--------------------------------------------------------------------------- */
static void write_tree(FILE *f, HuffNode *node,
                        unsigned char *byte, int *bit_pos) {
    int i;
    if (node->ch != -1) {
        /* Leaf */
        write_bit(f, byte, bit_pos, 1);
        for (i = 7; i >= 0; i--)
            write_bit(f, byte, bit_pos, (node->ch >> i) & 1);
    } else {
        /* Internal */
        write_bit(f, byte, bit_pos, 0);
        write_tree(f, node->left,  byte, bit_pos);
        write_tree(f, node->right, byte, bit_pos);
    }
}

int compress(const char *input_path, char output[50]) {
    /* ALL declarations at the top -- required by C89 */
    FILE         *in;
    FILE         *out;
    HuffNode     *root;
    long          freq[256];
    char          codes[256][MAX_CODE_LEN];
    char          buf[MAX_CODE_LEN];
    unsigned char byte    = 0;
    int           bit_pos = 0;
    int           ch;
    int           i;
    unsigned int  total   = 0;

    in = fopen(input_path, "rb");
    if (!in) { perror("compress: fopen input"); return 1; }

    /* 1. Count character frequencies */
    count_frequency(in, freq);
    rewind(in);

    /* 2. Build Huffman tree and generate bit-codes */
    root = build_huffman_tree(freq);
    if (!root) { fclose(in); fprintf(stderr, "compress: empty file\n"); return 1; }

    memset(codes, 0, sizeof(codes));
    generate_codes(root, codes, buf, 0);

    /* 3. Open output file */
    out = fopen(strcat(output, ".g5"), "wb");
    if (!out) { perror("compress: fopen output"); fclose(in); return 1; }

    /* 4. Write header:
          [uint32 total_chars] then the Huffman tree packed as bits.
          The data bits follow immediately in the same byte stream.        */
    for (i = 0; i < 256; i++) total += (unsigned int)freq[i];
    fwrite(&total, sizeof(unsigned int), 1, out);   /* 4 bytes */

    write_tree(out, root, &byte, &bit_pos);         /* ~30 bytes for 24 syms */

    /* 5. Encode and write each character */
    while ((ch = fgetc(in)) != EOF) {
        for (i = 0; codes[ch][i]; i++)
            write_bit(out, &byte, &bit_pos, codes[ch][i] == '1');
    }

    /* Flush any remaining bits */
    if (bit_pos > 0)
        fwrite(&byte, 1, 1, out);

    fclose(in);
    fclose(out);
    free_tree(root);
    return 0;
}

#endif /* COMPRESS_H */