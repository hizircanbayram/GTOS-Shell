#ifndef WC_H_HCB
#define WC_H_HCB



#define WC_ONE_ARG(argc) ((argc == 2) ? 1 : 0)
#define WC_REDIRECT(argc) ((argc == 3) ? 1 : 0)

#define ONE_ARGUMENT 1
#define INPUT_REDIRECT 2
#define OUTPUT_REDIRECT 3
#define PIPE_REDIRECT 4

/*
PARAMETERS
fileName : name of the file whose content is written into
flag : indicate either of the operations : one argument, redirect types or pipe*/
int wcTo(const char *fileName, int flag);

#endif
