#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dirent.h>
#include	<sys/stat.h>
#include    "lsf.h"



int main(int argc, char **argv) {
    argumentNumberControl(argc);
    DIR *curDir = NULL;
    int pipeArr[2];
    char *redirectFileName;
    int isPipe;
    printf("argc : %d\n", argc);
    if (LSF_NO_OPTION(argc)) {
        curDir = opendir(".");
        redirectFileName = NULL;
        isPipe = 0;
    }
    else if (LSF_REDIRECT(argc)) { // REDIRECT ATLANDI SU AN
        printf("redirect\n");
        if (!strcmp("m>", argv[1])) {
        printf("redirect >\n");
            curDir = opendir(".");
            redirectFileName = (char *) malloc(sizeof(char) * 1024);
            strcpy(redirectFileName, argv[2]);
            isPipe = 0; 
        }
        else if (!strcmp("m<", argv[1])) {
        printf("redirect <\n");
            char *fileContent = NULL;
            size_t len = 0;
            FILE *fp = fopen(argv[2], "r");
            if (!fp) {
                fprintf(stderr, "File %s couldn't be found.\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            getline(&fileContent, &len, fp); // fileContent has a path for the directory whose files are displayed
            redirectFileName = NULL;
            isPipe = 0;
            printf("\n\nfileContent : (%s)\n\n\n", fileContent);
            curDir = opendir(fileContent);
        }
        else if (!strcmp("|", argv[1])) {

        }

    }
    directoryOpenControl(curDir); // since curDir is not used so far and it will be used below, it can be checked here
    struct dirent *curFile = NULL;
    struct stat curFileStat;
	while ((curFile=readdir(curDir)) != NULL) { // takes every file in the directory
        if (!strcmp(".", curFile->d_name) || !strcmp("..", curFile->d_name))
            continue;
		if (curFile->d_type != DT_DIR) { // If the file is not a directory
            int statRetVal = stat(curFile->d_name, &curFileStat);
            statOpenControl(statRetVal, curFile->d_name);
            writeInfos(curFile->d_name, curFileStat, pipeArr, redirectFileName, isPipe);
        }
    }

    free(redirectFileName);
}



void argumentNumberControl(int argc) {
    if (argc > 3) {
        fprintf(stderr, "More arguments than intended.\n");
        exit(EXIT_FAILURE);
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



void writeInfos(const char *fileName, const struct stat curFileStat, const int *pipeArr, const char *redirectFileName, int isPipe) {
    if (redirectFileName) {
        FILE *fp = fopen(redirectFileName, "w");
        if (!fp) {
            fprintf(stderr, "file %s couldn't be opened for some reason.\n", redirectFileName);
            exit(EXIT_FAILURE);
        }
        else {
            fprintf( fp, "%s\t", fileName);
		    fprintf( fp, (S_ISREG(curFileStat.st_mode)) ? "R" : "S");
		    fprintf( fp, (curFileStat.st_mode & S_IRUSR) ? "r" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IWUSR) ? "w" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IXUSR) ? "x" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IRGRP) ? "r" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IWGRP) ? "w" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IXGRP) ? "x" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IROTH) ? "r" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IWOTH) ? "w" : "-");
		    fprintf( fp, (curFileStat.st_mode & S_IXOTH) ? "x" : "-");
		    fprintf( fp, "\t%ld\n",curFileStat.st_size);
        }
    }
    else if (isPipe) {

    }
    else {
        printf( "%s\t", fileName);
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
	    printf("\t%ld\n",curFileStat.st_size);
    }
}
