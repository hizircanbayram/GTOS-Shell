#include    "shell.h"



int main() {
    char** arglist;
    char* cmdline;
    char* prompt = PROMPT;   
    int argNumber = 0;
    while((cmdline = read_cmd(prompt,stdin))){
        if((arglist = tokenize(cmdline, &argNumber))){
            execute(arglist, argNumber);
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



int execute(char* arglist[], int argc){
    if ((strcmp("./pwd", arglist[0])) &&
        (strcmp("./lsf", arglist[0]))  &&
        (strcmp("./cat", arglist[0])) &&
        (strcmp("./wc", arglist[0]))  &&
        (strcmp("./bunedu", arglist[0])) )
        return -1;

    if ((!strcmp("./pwd", arglist[0]) && (argc == 1))) {
        //printf("pwd without pipe\n");
        return execWithoutPipe(arglist);
    }
    else if ((!strcmp("./pwd", arglist[0]) && (argc > 1) && (!strcmp("|", arglist[1])))) {
        //printf("pwd with pipe\n");
        return execWithPipe(arglist[0], NULL, arglist[2]); 
    }

    else if ((!strcmp("./lsf", arglist[0]) && (argc == 1))) {
        //printf("lsf without pipe\n");
        return execWithoutPipe(arglist);
    }
    else if ((!strcmp("./lsf", arglist[0]) && (argc > 1) && (!strcmp("|", arglist[1])))) {
        //printf("lsf with pipe\n");
        return execWithPipe(arglist[0], NULL, arglist[2]); 
    }

    else if ((strcmp("./lsf", arglist[0]) && (strcmp("./pwd", arglist[0])))) {
        if ((argc > 2) && (strcmp(arglist[2], "|"))) {
            //printf("other without pipe\n");
            return execWithoutPipe(arglist);
        }
        if ((argc > 3) && (!strcmp(arglist[2], "|"))) {
            //printf("other with pipe\n");
            return execWithPipe(arglist[0], arglist[1], arglist[3]); 
        }
        if ((argc == 1)) {
            //printf("other without pipe\n");
            return execWithoutPipe(arglist);
        }
    }
    return execWithoutPipe(arglist);
}


// The Linux Programming Interface p900, originated
int execWithPipe(const char *cmd1, const char *cmd2, const char *cmd3) {
	int pfd[2]; /* Pipe file descriptors */
	if (pipe(pfd) == -1) /* Create pipe */
         fprintf(stderr, "execlp");
	switch (fork()) {
	 	case -1:
            fprintf(stderr, "execlp");
	 	case 0: /* First child: exec 'ls' to write to pipe */
	 		if (close(pfd[0]) == -1) /* Read end is unused */
            fprintf(stderr, "execlp");
 			if (pfd[1] != STDOUT_FILENO) { /* Defensive check */
 				if (dup2(pfd[1], STDOUT_FILENO) == -1)
                    fprintf(stderr, "execlp");
 				if (close(pfd[1]) == -1)
                    fprintf(stderr, "execlp");
 			}
            if (!strcmp("./pwd", cmd1)) {
                execlp(cmd1, cmd1, (char *) NULL);
            }
            else if (!strcmp("./lsf", cmd1)) {
                execlp(cmd1, cmd1, (char *) NULL);
            }
            else if ((!strcmp("./bunedu", cmd1)) || (!strcmp("./cat", cmd1)) || (!strcmp("./wc", cmd1))) {
                execlp(cmd1, cmd1, cmd2, (char *) NULL);
            }
            fprintf(stderr, "execlp");
 		default: /* Parent falls through to create next child */
 			break;
 	}
 	
 	switch (fork()) {
 		case -1:
            fprintf(stderr, "execlp");
 		case 0: /* Second child: exec 'wc' to read from pipe */
 			if (close(pfd[1]) == -1) /* Write end is unused */
                fprintf(stderr, "execlp");
 			/* Duplicate stdin on read end of pipe; close duplicated descriptor */
 			if (pfd[0] != STDIN_FILENO) { /* Defensive check */
 				if (dup2(pfd[0], STDIN_FILENO) == -1)
                    fprintf(stderr, "execlp");
 				if (close(pfd[0]) == -1)
                    fprintf(stderr, "execlp");
 			}
 			execlp(cmd3, cmd3, (char *) NULL); /* DEGISECEK!!! */
            fprintf(stderr, "execlp");
 		default: /* Parent falls through */
 			break;
 	}

 	if (close(pfd[0]) == -1)
        fprintf(stderr, "execlp");
 	if (close(pfd[1]) == -1)
        fprintf(stderr, "execlp");
 	if (wait(NULL) == -1)
        fprintf(stderr, "execlp");
 	if (wait(NULL) == -1)
        fprintf(stderr, "execlp");
 	exit(EXIT_SUCCESS);
}



int execWithoutPipe(char *arglist[]) {
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



char** tokenize(char* cmdline, int *argNumber){
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
    *argNumber = arg_ind;
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
