#include    <stdio.h>
#include    <stdlib.h>
#include    "wc.h"



int main(int argc, char **argv) {
    if (WC_ONE_ARG(argc)) {
        int lineNumber = wcTo(argv[1], ONE_ARGUMENT); 
        printf("%d\n", lineNumber);
    }
    else if (WC_REDIRECT(argc)) {

    }    
    else {
        fprintf(stderr, "Invalud number of arguments are supplied.\n");
    }

}



int wcTo(const char *fileName, int flag) {
    int lineNumber = 0;
    FILE *fp = fopen(fileName, "r");
    if (!fp && fileName) {
        fprintf(stderr, "File %s couldn't be opened for some reason.\n", fileName);
        exit(EXIT_FAILURE);
    }
    if (ONE_ARGUMENT == flag) {
        char *line = NULL;
        size_t len = 0;
        while (getline(&line, &len, fp) != -1) {
            free(line);        
            line = NULL;
            ++lineNumber;
        }
       
    }
    else if (INPUT_REDIRECT == flag) {

    }
    else if (OUTPUT_REDIRECT == flag) {

    } 
    else if (PIPE_REDIRECT == flag) {

    }
    else {
        fprintf(stderr, "There is a bug in design of the program. writeTo function else statement is executed.\n");
    }
    return lineNumber;
}
