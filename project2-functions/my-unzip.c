#include <stdio.h>
#include <stdlib.h>


//To decompress the file, this guide for fread was used: https://www.geeksforgeeks.org/fread-function-in-c/
//To print out, found out about this function (putchar) from here: https://www.geeksforgeeks.org/putchar-function-in-c/


// decompressFile reads a compressed file from files, then writes out the decompressed text.
void decompressFile(FILE *files) {
    int count;   // Run length (4 bytes)
    char ch;     // The character (1 byte)
    
    // Loop through 5 byte blocks
    // fread will return the number of elements that have been read
    while (fread(&count, sizeof(int), 1, files) == 1) {
        //Read the associated character
        if (fread(&ch, sizeof(char), 1, files) != 1) {
            break; //exit the loop, if not possible to read
        }
        // Output the character 'count' times.
        for (int i = 0; i < count; i++) {
            putchar(ch);
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    int ErrorOccured=0;
    
    // Process each file.
    for (int i = 1; i < argc; i++) {
        FILE *files = fopen(argv[i], "rb"); // Open in binary mode.
        if (files == NULL) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[i]);
            ErrorOccured=1;
            continue;
        }
        //Decompress the file
        decompressFile(files);
        fclose(files);
    }
    
    return ErrorOccured ? 1 : 0;
}
