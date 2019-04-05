#ifndef LSF_H
#define LSF_H

#include    <dirent.h>


/*
Parameters
fileName : name of file whose infos are written into
curFileStat : struct of the file that keeps its infos
pipeArr : addresses of pipe, if it is written into a pipe
redirectFileName : name of the file where I/O is redirected to
*/
void writeInfos(const char *fileName, const struct stat curFileStat, const int *pipeArr, FILE* redirect_fp,  const char *opr);

void directoryOpenControl(const DIR* curDirPtr);
void statOpenControl(int statRetVal, const char *name);
void argumentNumberControl(int argc);

#define LSF_NO_OPTION(a) ((a == 1) ? (1) : (0))
#define LSF_REDIRECT(a)  ((a == 3) ? (1) : (0))

#endif
