#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    // handling the number of commandline arguments
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    FILE *inFile = stdin;   // default to stdin
    FILE *outFile = stdout; // default to stdout

    // open files according to the given arguments
    if (argc >= 2)
    {
        // opening input file
        inFile = fopen(argv[1], "r");
        if (inFile == NULL)
        {
            fprintf(stderr, "cannot open file '%s'\n", argv[1]);
            return 1;
        }
    }
    if (argc == 3)
    {
        // opening output file
        outFile = fopen(argv[2], "w");
        if (outFile == NULL)
        {
            fprintf(stderr, "cannot open file '%s'\n", argv[2]);
            if (inFile != stdin)
                fclose(inFile);
            return 1;
        }
    }

    // read lines into memory
    size_t capacity = 8; // initial array size
    size_t size = 0;     //  actual number of lines
    char **lines = malloc(sizeof(char *) * capacity);

    char *buffer = NULL; // for getline() function
    size_t bufsize = 0;  // for getline() function
    ssize_t linelen;

    // read lines until EOF
    while ((linelen = getline(&buffer, &bufsize, inFile)) != -1)
    {
        // if the array is full, increase its size
        if (size == capacity)
        {
            capacity *= 2;
            lines = realloc(lines, sizeof(char *) * capacity);
        }

        // memory allocation
        lines[size] = malloc(linelen + 1);
        // copy the read line
        strncpy(lines[size], buffer, linelen + 1);
        size++;
    }

    free(buffer); // free the buffer memory

    // print the lines in reverse order
    for (ssize_t i = size - 1; i >= 0; i--)
    {
        fprintf(outFile, "%s", lines[i]);
        free(lines[i]); // free the line memory
    }
    free(lines); // free the array memory

    // close the file if it was opened
    if (inFile != stdin)
        fclose(inFile);
    if (outFile != stdout)
        fclose(outFile);

    return 0; // program terminates
}
