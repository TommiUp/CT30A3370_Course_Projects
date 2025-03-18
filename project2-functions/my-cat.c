#include <stdio.h>
#include <string.h>
#include <errno.h>

// Inspiration for the code, and copied some of the approaches here: https://www.geeksforgeeks.org/build-your-own-cat-command-in-c-for-linux/
// Usage of fgets was learned from here and utilized via example: https://www.geeksforgeeks.org/fgets-function-in-c/

#define BUFFER 2048 // Define the buffer size

// Opens a file and prints the content into standard output
int printFileContent(const char *file)
{

    FILE *files = fopen(file, "r");

    if (files == NULL)
    {
        fprintf(stderr, "my-cat: cannot open file '%s': ", file);
        perror("");
        return 1;
    }

    // Declare buffer

    char buffer[BUFFER];

    // Read from file until the end, insert into buffer
    while (fgets(buffer, BUFFER, files) != NULL)
    {

        // Print the line into the output
        printf("%s", buffer);
    }

    // Close the file
    fclose(files);

    return 0;
}

int main(int argc, char *argv[])
{
    // Check for all arguments
    if (argc < 2)
    {
        return 0;
    }

    int exit_code = 0;

    // Loop through all files that are given, skipping ofcourse the argv[0]
    for (int i = 1; i < argc; i++)
    {
        if (printFileContent(argv[i]) != 0)
        {
            exit_code = 1; // If any file fails, return error status
        }
    }

    return exit_code;
}
