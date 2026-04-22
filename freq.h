//Shanmukh
//TODO:
// Read the file given by the main and
// Count how many time the each letter is repeating
#ifndef FREQ_H
#define FREQ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

static void count_frequency(FILE *f, long freq[256]) {
    memset(freq, 0, sizeof(long) * 256);
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        freq[ch]++;
    }
}

static void print_frequency(long freq[256]){
    printf("%-10s %s\n", "CHAR", "COUNT");
    printf("--------------------\n");
    for (int i = 0; i < 256; i++){
        if (freq[i] > 0) {
            if      (i == '\n') printf("'\\n'      : %ld\n", freq[i]);
            else if (i == '\t') printf("'\\t'      : %ld\n", freq[i]);
            else if (i == ' ')  printf("' '       : %ld\n", freq[i]);
            else                printf("'%c'       : %ld\n", i, freq[i]);
        }
    }
}
#endif