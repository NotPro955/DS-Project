#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freq.h"
#include "compress.h"

void usage_print(){
    printf("Invalid Command\n");
    printf("./main <filename> --compress\n");
    printf("./main <filename> --decompress\n");
}

int main(int argc, char *argv[]){
    if (argc != 3){
        usage_print();
        return 1;
    }
    else{
        if(strcmp(argv[2],"--compress")==0){
            FILE* f = fopen(argv[1], "r");
            if (!f){
                printf("Unable to Access the file\n");
                return 1;
            }
 
            long freq[256];
            count_frequency(f, freq);
            FILE* cf = fopen("compressed.g5","wb");
            compress(f,cf,freq);
            fclose(f);
            print_frequency(freq);
        }
        else if(strcmp(argv[2],"--decompress")==0){
            printf("Hello\n");
        }
        else{
            usage_print(argv[0]);
        }
    }
    return 0;
}
