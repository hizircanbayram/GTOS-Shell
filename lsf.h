#ifndef LSF_H
#define LSF_H

#include    <dirent.h>

void writeInfos(const struct stat curFileStat);


void directoryOpenControl(const DIR* curDirPtr);
void statOpenControl(int statRetVal, const char *name);

#endif
