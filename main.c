#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freq.h"
#include "compress.h"
#include "decompress.h"

void usage_print(){
    printf("Invalid Command\n");
    printf("./main <filename> --compress\n");
    printf("./main <filename> --decompress\n");
}

long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    long size;

    if (!file) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);

    return size;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        usage_print();
        return 1;
    }
    else{
        if(strcmp(argv[2],"--compress")==0){
            FILE* file = fopen(argv[1], "r");
            if (!file){
                printf("Unable to Access the file\n");
                return 1;
            }
 
            long freq[256];
            count_frequency(file, freq);
            fclose(file);
            print_frequency(freq);

            char output[50];
            printf("Enter out compressed file name: ");
            scanf("%s", output);
            printf("Output file name: %s", output);

            if (compress(argv[1], output) == 0) {
                char compressed_file[60];

                strcpy(compressed_file, output);

                printf("Compressed: %s -> %s\n", argv[1], compressed_file);
                printf("Original size: %ld bytes\n", get_file_size(argv[1]));
                printf("Compressed size: %ld bytes\n", get_file_size(compressed_file));
            }
            else {
                return 1;
            }
        }
        else if (strcmp(argv[2], "--decompress") == 0) {
            if (argc != 3) { usage_print(); return 1; }
            char output[50];
            printf("Enter output decompressed file name: ");
            scanf("%s", output);
            printf("Output file name: %s", output);
            if (decompress(argv[1], output) == 0) {
                char decompressed_file[60];

                strcpy(decompressed_file, output);

                printf("Decompressed: %s -> %s\n", argv[1], decompressed_file);
                printf("Compressed size: %ld bytes\n", get_file_size(argv[1]));
                printf("Decompressed size: %ld bytes\n", get_file_size(decompressed_file));
            }
            else {
                return 1;
            }
        }
        else{
            usage_print();
        }
    }
    return 0;
}
