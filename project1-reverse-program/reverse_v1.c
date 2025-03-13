#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    FILE *inFile = stdin; // default to stdin
    if (argc == 2)
    {
        // attempt to open the file without error checking
        inFile = fopen(argv[1], "r");
    }

    size_t capacity = 8; // initial array size
    size_t size = 0;     //  actual number of lines
    char **lines = malloc(capacity * sizeof(char *));

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
            lines = realloc(lines, capacity * sizeof(char *));
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
        printf("%s", lines[i]);
        free(lines[i]); // free the line memory
    }
    free(lines); // free the array memory

    // close the file if it was opened
    if (inFile != stdin)
    {
        fclose(inFile);
    }

    return 0; // program terminates
}
