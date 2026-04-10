// Hrushikesh
// Hrushikesh
// Todo: 
// 1) Read the file name through CLI
// 2) Pass the filename to the shanmukh's file
// 3) Ask the user if to compress the file or decompress it?
// 4) Manange the errors

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Error: Invalid Argument\nUsage eg: ./main testing.txt");
        return 1;
    }
    else{
        while(1){
            printf("\n----------------------------------------------------------------\n");
            printf("1) Compress the file\n2) DeCompress the flie\n3) Exit\n");
            printf("Enter(eg. 1/2/3): ");
            int ch;
            scanf("%d",&ch);
            printf("\n----------------------------------------------------------------\n");

            switch(ch){
                case 1:printf("\nCompressing the file\n");break;
                case 2:printf("\nDecomprssing the file\n");break;
                case 3:return 0; break;
                default: printf("\nInvalid Choice\n");
            }
        }
    }