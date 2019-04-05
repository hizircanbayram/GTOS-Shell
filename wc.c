#include    "wc.h"



int main(int argc, char **argv) {
    int pipeArr[2];
    char c;
    int lineNumber = 0;
    if (argc == 1) {
        while (scanf("%c", &c) != EOF) {
            if (c == '\n')
                ++lineNumber;
        }
        printf("%d\n", lineNumber);
    }
    else if (WC_ONE_ARG(argc)) {
        wcTo(argv[1], ONE_ARGUMENT, pipeArr, NULL); 
    }
    else if (WC_REDIRECT(argc)) {
        if (!strcmp(">", argv[2])) {
            wcTo(argv[1], OUTPUT_REDIRECT, pipeArr, argv[3]);
        }
        else if (!strcmp("<", argv[1])) {
            wcTo(NULL, INPUT_REDIRECT, pipeArr, argv[2]);
        }
        else if (!strcmp("|", argv[2])) {
            wcTo(argv[1], PIPE_REDIRECT, pipeArr, argv[3]);
        }
        else {
            fprintf(stderr, "WC | Undefined operation.\n");
            exit(EXIT_FAILURE);
        }
        
    }    
    else {
        fprintf(stderr, "WC | Invalid number of arguments are supplied.\n");
    }
    return 0;
}



int wcTo(const char *fileName, int flag, const int *pipeArr, const char *redirectFileName) {
    int lineNumber = 0;
    FILE *fp = fopen(fileName, "r");
    if (!fp && fileName) {
        fprintf(stderr, "WC | Reading file %s for printing couldn't be opened for some reason.\n", fileName);
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
        printf("%d\n", lineNumber);
    }
    else if (INPUT_REDIRECT == flag) {
        char *line = NULL;
        size_t len = 0;
        FILE *redirect_fp = fopen(redirectFileName, "r");
        if (!redirect_fp) {
            fprintf(stderr, "WC | File %s couldn't be opened for input redirecting.\n", redirectFileName);
            exit(EXIT_FAILURE);
        } 
        while (getline(&line, &len, redirect_fp) != -1) {
            free(line);        
            line = NULL;
            ++lineNumber;
        }
        printf("%d\n", lineNumber);
        fclose(redirect_fp);
    }
    else if (OUTPUT_REDIRECT == flag) {
        char *line = NULL;
        size_t len = 0;
        FILE *redirect_fp = fopen(redirectFileName, "w");
        if (!redirect_fp) {
            fprintf(stderr, "WC | File %s couldn't be opened for output redirecting.\n", redirectFileName);
            exit(EXIT_FAILURE);
        } 
        while (getline(&line, &len, fp) != -1) {
            free(line);        
            line = NULL;
            ++lineNumber;
        }
        fprintf(redirect_fp, "%d\n", lineNumber);
        fclose(redirect_fp);
    } 
    else if (PIPE_REDIRECT == flag) {

    }
    else {
        fprintf(stderr, "There is a bug in design of the program. writeTo function else statement is executed.\n");
    }
    fclose(fp);
    return lineNumber;
}
