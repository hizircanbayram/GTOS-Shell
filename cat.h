#ifndef CAT_H_HCB
#define CAT_H_HCB

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#define CAT_ONE_ARG(argc) ((argc == 2) ? 1 : 0)
#define CAT_REDIRECT(argc) (((argc == 3) || (argc == 4)) ? 1 : 0)

#define ONE_ARGUMENT 1
#define INPUT_REDIRECT 2
#define OUTPUT_REDIRECT 3
#define PIPE_REDIRECT 4

/*
PARAMETERS
fileName : name of the file whose content is written into
flag : indicate either of the operations : one argument, redirect types or pipe*/
void writeTo(const char *fileName, int flag, const int *pipeArr, const char *redirectFileName);

#endif
