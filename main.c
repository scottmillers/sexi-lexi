#include <stdio.h>
#include <stdlib.h> // For exit()

int main(int argc, char *argv[]) {
    FILE *file;

    // Check if the program was run with exactly one argument (the input file name)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_source_file>\n", argv[0]);
        exit(2);
    }

    // Try to open the file for reading
    file = fopen(argv[1], "r");
    if (file == NULL) {
        // If fopen() returned NULL, the file could not be opened
        perror("Error opening file"); // send to standard error stream
        exit(3);
    }

    printf("DCooke Parser :: R11770217\n");
    
    //lex(fp);
    //P(fp);
    // If the file is successfully opened, you can continue with your program logic here
    // For example, reading from the file
    // ...

    // Don't forget to close the file when you're done
    fclose(file);

    return 0; // Exit with code 0 indicating success
}

    
