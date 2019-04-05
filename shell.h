#ifndef SHELL_H_HCB
#define SHELL_H_HCB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_LEN 512
#define ARGLEN 30
#define MAXARGS 10
#define PROMPT "GTOS-Shell: "

int execute(char* arglist[], int argc);
int execWithPipe(const char *cmd1, const char *cmd2, const char *cmd3);
int execWithoutPipe(char *arglist[]);
char** tokenize(char* cmdline, int *argNumber);
char* read_cmd(char* prompt, FILE* fp);

#endif
