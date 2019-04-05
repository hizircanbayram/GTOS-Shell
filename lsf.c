#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dirent.h>
#include	<sys/stat.h>
#include    "lsf.h"


int main(int argc, char **argv) {
    argumentNumberControl(argc);
    DIR *curDir = NULL;
    // parameters for writeInfos function
    int pipeArr[2];
    char *redirectFileName = NULL;
    char opr[2] = { 0 };
    FILE* redirect_fp = NULL;
    if (LSF_NO_OPTION(argc)) {
        curDir = opendir(".");
        redirectFileName = NULL; 
        opr[0] = '.';
    }
    else if (LSF_REDIRECT(argc)) { 
        if (!strcmp(">", argv[1])) {
            curDir = opendir(".");
            redirect_fp = fopen(argv[2], "w");
            if (!redirect_fp) {
                fprintf(stderr, "file %s couldn't be opened for some reason.\n", redirectFileName);
                exit(EXIT_FAILURE);
            }
            redirectFileName = argv[2];
            opr[0] = '>';
        }
        else if (!strcmp("<", argv[1])) {
            char *fileContent = NULL;
            size_t flag_len;
            redirect_fp = fopen(argv[2], "r");
            if (!redirect_fp) {
                fprintf(stderr, "File %s couldn't be found.\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            size_t dirNameSize = getline(&fileContent, &flag_len, redirect_fp); // fileContent has a path for the directory whose files are displayed
            fileContent[dirNameSize - 1] = '\0';
            curDir = opendir(fileContent);
            redirectFileName = argv[2];
            opr[0] = '<';
            free(fileContent);
        }
        else if (!strcmp("|", argv[1])) {

        }
        else {
            fprintf(stderr, "Undefined operation.\n");
            exit(EXIT_FAILURE);
        }
    }
    directoryOpenControl(curDir); // since curDir is not used so far and it will be used below, it can be checked here
    struct dirent *curFile = NULL;
    struct stat curFileStat;
	while ((curFile=readdir(curDir)) != NULL) { // takes every file in the directory
        if (!strcmp(".", curFile->d_name) || !strcmp("..", curFile->d_name))
            continue;
		if (curFile->d_type != DT_DIR) { // If the file is not a directory
            int statRetVal = lstat(curFile->d_name, &curFileStat);
            statOpenControl(statRetVal, curFile->d_name);
            writeInfos(curFile->d_name, curFileStat, pipeArr, redirect_fp, opr);
        }
    }
    closedir(curDir);
    return 0;
}



void argumentNumberControl(int argc) {
    if (argc > 3 || argc == 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
}



void directoryOpenControl(const DIR* curDirPtr) {
    if (!curDirPtr) {
        fprintf(stderr, "The current directory couldn't be opened for some reason.\n");
        exit(EXIT_FAILURE);
    }
}



// HATA DONDURUYOR AMA OKUYOR??
void statOpenControl(int statRetVal, const char *name) {
    if (statRetVal < 0) {
        fprintf(stderr, "Stat of %s couldn't be opened for some reason.\n", name);
        //exit(EXIT_FAILURE);
    }
}



void writeInfos(const char *fileName, const struct stat curFileStat, const int *pipeArr, FILE* fp, const char *opr) {
    if (!strcmp(opr, ">")) { 
        // redirectFileName != NULL, isPipe == 0, opr == ">"
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
    else if (!strcmp(opr, "|")) {
        // redirectFileName == NULL, isPipe == 1, opr == "|"
    }
    else if (!strcmp(opr, "<") || !strcmp(opr, ".")) { // both, printing stdout
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
