#include    "cat.h"




int main(int argc, char **argv) {
    int pipeArr[2];
    if (CAT_ONE_ARG(argc)) {
        writeTo(argv[1], ONE_ARGUMENT, pipeArr, NULL); 
    }
    else if (CAT_REDIRECT(argc)) {
        if (!strcmp(">", argv[2])) {
            writeTo(argv[1], OUTPUT_REDIRECT, pipeArr, argv[3]);
        }
        else if (!strcmp("<", argv[1])) {
            writeTo(NULL, INPUT_REDIRECT, pipeArr, argv[2]);
        }
        else if (!strcmp("|", argv[2])) {
            writeTo(argv[1], PIPE_REDIRECT, pipeArr, argv[3]);
        }
        else {
            fprintf(stderr, "CAT | Undefined operation.\n");
            exit(EXIT_FAILURE);
        }
        
    }    
    else {
        fprintf(stderr, "CAT | Invalid number of arguments are supplied.\n");
    }
    
    return 0;
}



void writeTo(const char *fileName, int flag, const int *pipeArr, const char *redirectFileName) {
    FILE *fp = fopen(fileName, "r");
    if (!fp && fileName) {
        fprintf(stderr, "CAT | Reading file %s for printing couldn't be opened for some reason.\n", fileName);
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
        char *line = NULL;
        size_t len = 0;
        FILE *redirect_fp = fopen(redirectFileName, "r");
        if (!redirect_fp) {
            fprintf(stderr, "CAT | File %s couldn't be opened for input redirecting.\n", redirectFileName);
            exit(EXIT_FAILURE);
        } 
        while (getline(&line, &len, redirect_fp) != -1) {
            printf("%s", line);
            free(line);        
            line = NULL;
        }
        fclose(redirect_fp);
    }
    else if (OUTPUT_REDIRECT == flag) {
        char *line = NULL;
        size_t len = 0;
        FILE *redirect_fp = fopen(redirectFileName, "w");
        if (!redirect_fp) {
            fprintf(stderr, "CAT | File %s couldn't be opened for output redirecting.\n", redirectFileName);
            exit(EXIT_FAILURE);
        } 
        while (getline(&line, &len, fp) != -1) {
            fprintf(redirect_fp, "%s", line);
            free(line);        
            line = NULL;
        }
        fclose(redirect_fp);
    } 
    else if (PIPE_REDIRECT == flag) {

    }
    else {
        fprintf(stderr, "There is a bug in design of the program. writeTo function else statement is executed.\n");
    }
    fclose(fp);
}
