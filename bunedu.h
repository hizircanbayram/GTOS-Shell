#ifndef H_DU_V1
#define H_DU_V1

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include   	<dirent.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<errno.h>

#define BUNEDU_ONE_ARG(argc) ((argc == arg_limit) ? 1 : 0)
#define BUNEDU_REDIRECT(argc) (((argc == (arg_limit + 1)) || (argc == (arg_limit + 2))) ? 1 : 0)

#define ONE_ARGUMENT 1
#define INPUT_REDIRECT 2
#define OUTPUT_REDIRECT 3
#define PIPE_REDIRECT 4

void argcControl(int argc, char **argv);
char* argvControl(int argc, char **argv); 
int sizepathfun (char *path);
int postOrderApplyPrivate(char *path, int pathfun (char *path1), const int *pipeArr, const char *redirectFileName, FILE *write_fp);
void postOrderApply(char *path, int pathfun (char *path1), const int *pipeArr, const char *redirectFileName, int argc, char **argv, FILE *write_fp);

#endif
