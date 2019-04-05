#ifndef PWD_H_HCB
#define PWD_H_HCB

#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    <string.h>

#define CAT_ONE_ARG(argc) ((argc == 1) ? 1 : 0)
#define CAT_REDIRECT(argc) ((argc == 3) ? 1 : 0)

#define ONE_ARGUMENT 1
#define OUTPUT_REDIRECT 3
#define PIPE_REDIRECT 4

#endif
