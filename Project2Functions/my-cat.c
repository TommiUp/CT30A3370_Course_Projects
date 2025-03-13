#include <stdio.h>
#include <string.h>

//Inspiration for the code, and copied some of the approaches here: https://www.geeksforgeeks.org/build-your-own-cat-command-in-c-for-linux/
//Usage of fgets was learned from here and utilized via example: https://www.geeksforgeeks.org/fgets-function-in-c/





#define BUFFER 2048 //Define the buffer size


//Opens a file and prints the content into standard output
void printFileContent(const char* file){

    FILE* files = fopen(file, "r");

    if (files==NULL){
        printf("Cannot open a file");
        return;
    }

    //Declare buffer

    char buffer[BUFFER];

    //Read from file until the end, insert into buffer 
    while(fgets(buffer, BUFFER, files) != NULL){

        //Print the line into the output
        printf("%s", buffer);
    }

    //Close the file
    fclose(files);


}

int main(int argc, char *argv[]){
    //Check for all arguments
    if (argc < 2){
        printf("Not enough arguments");
        return 0;
    }


    //Loop through all files that are given, skipping ofcourse the argv[0]
    for (int i = 1; i < argc; i++) {
        printFileContent(argv[i]);
    }

    return 0;

}

