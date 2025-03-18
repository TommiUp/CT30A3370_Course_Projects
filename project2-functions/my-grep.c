#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Inspiration for the code is found here, on how to implement the grep command: https://www.quora.com/How-do-you-write-a-C-program-to-mimic-grep-command-in-Linux
// For the getline implementation in the code this was used: https://c-for-dummies.com/blog/?p=1112
// Usage of strstr was learned from here: https://www.geeksforgeeks.org/strstr-in-ccpp/

// Function to read file and search for the given searchTerm
void ReadAndFindFileContent(FILE *fp, const char *searchTerm)
{
    char *line = NULL; // Pointer to store dynamically allocated line
    size_t len = 0;    // Size of the allocated buffer. (getline will determine the size)
    ssize_t nread;     // Number of character to read

    // Read each line
    // Getline will return -1 if no lines.
    while ((nread = getline(&line, &len, fp)) != -1)
    {
        if (strstr(line, searchTerm) != NULL)
        {                       // strstr check if the searchTerm existis within the line
            printf("%s", line); // Prints the line
        }
    }
    free(line); // Free the dynamically allocated memory.
}

int main(int argc, char *argv[])
{

    // Check if there is enough arguments
    if (argc < 2)
    {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        return 1;
    }
    // Search term itself
    const char *searchTerm = argv[1];
    int exit_code = 0;
    // If there is searchTerm but no file, read from standard input
    if (argc == 2)
    {
        // Read from standard input.
        ReadAndFindFileContent(stdin, searchTerm);
    }
    else
    {
        // Process each file provided on the command line.
        for (int i = 2; i < argc; i++)
        {
            FILE *files = fopen(argv[i], "r");
            if (files == NULL)
            {
                fprintf(stderr, "my-grep: cannot open file '%s'\n", argv[i]);
                exit_code = 1; // Continue to the next file but return 1 at the end
                continue;
            }
            // Call the function to search for term
            ReadAndFindFileContent(files, searchTerm);
            fclose(files); // Close
        }
    }
    return exit_code;
}
