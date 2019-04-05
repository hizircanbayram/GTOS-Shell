#include    "shell.h"



int main() {
    char** arglist;
    char* cmdline;
    char* prompt = PROMPT;   
    while((cmdline = read_cmd(prompt,stdin))){
        if((arglist = tokenize(cmdline))){
            execute(arglist);
            //  need to free arglist
           for(int k = 0; k < MAXARGS + 1; ++k)
               free(arglist[k]);
               free(arglist);
               free(cmdline);
         }
    }
    printf("\n");
    return 0;
}



int execute(char* arglist[]){
   int status;
   int pid = fork();
   switch(pid) {
      case -1:
          fprintf(stderr, "Fork is failed for some reason.\n");
	      exit(1);
      case 0:
	      execvp(arglist[0], arglist); // second parameter is arglist because name of the program is an argument too
 	      perror("Command not found...");
	      exit(1);
      default:
	     waitpid(pid, &status, 0);
         return 0;
   }
}



char** tokenize(char* cmdline){
    char** arglist = (char **) malloc(sizeof(char *) * (MAXARGS + 1));
    for(int i = 0; i < MAXARGS + 1; ++i) {
	    arglist[i] = (char *) malloc(sizeof(char) * ARGLEN);
        memset(arglist[i], 0, sizeof(char) * ARGLEN); // # of arguments are usually less than 10. Thus, we need to fix rest of the elements with 0 so that we can know where to stop
    }
    if(cmdline[0] == '\0')//if user has entered nothing and pressed enter key
        return NULL;
    char *token = strtok(cmdline, " \t");
    int arg_ind = 0;
    for ( ; token; ++arg_ind) {
        strcpy(arglist[arg_ind], token);
        token = strtok(NULL, " \t");
    }
    //printf("arg num : %d\n", arg_ind);
    arglist[arg_ind] = NULL;
    return arglist;
}      


char* read_cmd(char* prompt, FILE* fp){
    printf("%s", prompt); // pwd eklenecek :D
    char *cmdline = NULL;
    size_t flag_len;
    size_t cmdsize = getline(&cmdline, &flag_len, stdin);
    cmdline[cmdsize - 1] = '\0';
    return cmdline;
}
