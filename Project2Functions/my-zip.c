#include <stdio.h>
#include <stdlib.h>


//Run lenght encoding was learned from this: https://www.geeksforgeeks.org/run-length-encoding/
// For the fgetc, https://www.geeksforgeeks.org/fgets-function-in-c/
// Found how to write into the file: https://www.geeksforgeeks.org/fwrite-in-c/


//Helper function, reads a file character by character and updates the run length encoding state
void processFile(FILE *fp, int *runCount, int *currentChar, int *firstChar) {
    int c; //Variable to hold the current character

    //Loop through file
    while ((c = fgetc(fp)) != EOF) {
        if (*firstChar) {
            //First character to be processed
            //set the character and set run to 1
            *currentChar = c;
            *runCount = 1;
            *firstChar = 0; //Mark that at least one character is processed
        } else {
            if (c == *currentChar) {
                //If c is same as current character increment the run count
                (*runCount)++;
            } else {

                //When new character is spotted
                //Write the current run
                // Write the current run as a 4-byte integer and
                //and current char as a single byte
                fwrite(runCount, sizeof(int), 1, stdout);
                fwrite(currentChar, sizeof(char), 1, stdout);
                
                // Start a new run.
                *currentChar = c;
                *runCount = 1;
            }
        }
    }
}








int main(int argc, char *argv[]) {
    //Check that file exist
    if (argc < 2) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        return 1;
    }
    
    //Run length encoding
    int runCount = 0;       // Count of consecutive occurrences.
    int currentChar = 0;    // The current character.
    int firstChar = 1;      // Flag: 1 means no character processed yet.
    
    // Process each file as a continuous stream.
    //Files are processed as one stream of text
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r"); //Text mode
        if (fp == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            return 1;
        }

        //Process the file
        processFile(fp, &runCount, &currentChar, &firstChar);
        fclose(fp);
    }
    
    // After processing all files, flush out the final run (if any).

    //Flush out the final run. This will ensure that last run is written.
    if (!firstChar) {
        fwrite(&runCount, sizeof(int), 1, stdout);
        fwrite(&currentChar, sizeof(char), 1, stdout);
    }
    
    return 0;
}