#include    <stdio.h>
#include    <stdlib.h>
#include    <dirent.h>
#include	<sys/stat.h>
#include    "lsf.h"


int main(int argc, char **argv) {
    DIR *curDir = opendir(".");
    directoryOpenControl(curDir);
    struct dirent *curFile = NULL;
    struct stat curFileStat;
	while ((curFile=readdir(curDir)) != NULL) { // takes every file in the directory
        if (!strcmp(".", curFile->d_name) || !strcmp("..", curFile->d_name))
            continue;
		if (curFile->d_type != DT_DIR) { // If the file is not a directory
            int statRetVal = stat(curFile->d_name, &curFileStat);
            statOpenControl(statRetVal, curFile->d_name);
            printf("%s\t", curFile->d_name);
            writeInfos(curFileStat);
        }
    }
}



void directoryOpenControl(const DIR* curDirPtr) {
    if (!curDirPtr) {
        fprintf(stderr, "The current directory couldn't be opened for some reason.\n");
        exit(EXIT_FAILURE);
    }
}


void statOpenControl(int statRetVal, const char *name) {
    if (statRetVal < 0) {
        fprintf(stderr, "Stat of %s couldn't be opened for some reason.\n", name);
        exit(EXIT_FAILURE);
    }
}


void writeInfos(const struct stat curFileStat) {
    printf( (S_ISREG(curFileStat.st_mode)) ? "R" : "S");
    printf( (curFileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (curFileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (curFileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (curFileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (curFileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (curFileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (curFileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (curFileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (curFileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t%ld",curFileStat.st_size);
    printf("\n");
}
