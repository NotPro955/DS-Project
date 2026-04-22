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

int compress(const char *input_path,char output[50]) {
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

    /* 3. Open output and write header (frequency table) */
    out = fopen(strcat(output,".5g"),"wb");
    if (!out) { perror("compress: fopen output"); fclose(in); return 1; }

    fwrite(freq, sizeof(long), 256, out);

    /* 4. Encode and write each character */
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
