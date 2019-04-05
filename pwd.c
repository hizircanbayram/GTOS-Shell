#include    "pwd.h"



int main(int argc, char **argv) {
    char pwdName[1024] = { 0 };
    getcwd(pwdName, 1024); 
    //int pipeArr[2] = { 0 };
    if (CAT_ONE_ARG(argc)) {
        printf("%s\n", pwdName);
    }
    else if (CAT_REDIRECT(argc)) {
        if (!strcmp(">", argv[1])) {
            FILE *redirect_fp = fopen(argv[2], "w");
            if (!redirect_fp) {
                fprintf(stderr, "PWD | File %s couldn't be opened for output redirecting.\n", argv[2]);
                exit(EXIT_FAILURE);
            } 
            fprintf(redirect_fp, "%s", pwdName);
            fclose(redirect_fp);
        }
        else if (!strcmp("|", argv[1])) {

        }
        else {
            fprintf(stderr, "PWD | Undefined operation.\n");
            exit(EXIT_FAILURE);
        }
        
    }    
    else {
        fprintf(stderr, "CAT | Invalid number of arguments are supplied.\n");
    }
    
    return 0;
}
