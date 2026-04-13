//Shanmukh
//TODO:
// Read the file given by the main and
// Count how many time the each letter is repeating
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

#define MAX_SYMBOLS 256
int freq(char file[]){
    FILE* rfile = fopen(file,"r");
    if (rfile == NULL){
        printf("Erorr: Unable to open the file\n");
        return 1;
    }
    else{
        long freq_count[256] = {0};
        int ch;

        while ((ch = fgetc(rfile)) != EOF) {
            freq_count[ch]++;
        }
        fclose(rfile);
    }
    
}
