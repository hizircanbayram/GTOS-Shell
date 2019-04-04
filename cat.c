#include    <stdio.h>
#include    <stdlib.h>
#include    "cat.h"




int main(int argc, char **argv) {
    if (CAT_ONE_ARG(argc)) {
        writeTo(argv[1], ONE_ARGUMENT); 
    }
    else if (CAT_REDIRECT(argc)) {

    }    
    else {
        fprintf(stderr, "Invalud number of arguments are supplied.\n");
    }
    
    

}



void writeTo(const char *fileName, int flag) {
    FILE *fp = fopen(fileName, "r");
    if (!fp && fileName) {
        fprintf(stderr, "File %s couldn't be opened for some reason.\n", fileName);
        exit(EXIT_FAILURE);
    }
    if (ONE_ARGUMENT == flag) {
        char *line = NULL;
        size_t len = 0;

        while (getline(&line, &len, fp) != -1) {
            printf("%s", line);
            free(line);        
            line = NULL;
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
}
