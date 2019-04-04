#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include    	<dirent.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<errno.h>
#include	"151044075.h"



int isOption = 0;


int main(int argc, char **argv) {	
	argcControl(argc); // checks if the number of given command line arguments are valid.
	char *path = argvControl(argc, argv); // checks if the given command line arguments are valid.
	unsigned int retVal = postOrderApply(path, sizepathfun);	
	if (argc == 3)
		printf("%d	%s\n", retVal / 1024, *(argv + 2)); 
	else  // argc == 2 
		printf("%d	%s\n", retVal / 1024, *(argv + 1)); 
	return EXIT_SUCCESS;
}



// Traverses the tree in a post order way so that all directories can be computed in some way. Susm up all the ordinary files, displays their values but specific files.
int postOrderApply(char *path, int pathfun (char *path1)) {
    DIR *curDir = opendir(path);
    if (!curDir) {
   	printf("the directory : %s couldn't be opened for some reason.\n", path);
    	return -1; 
    }    
    struct dirent *curFile;
    char relPath[1024] = { 0 };
    unsigned int file_size = 0;		// a directory's size and the other files' size together
    unsigned int local_size = 0;	// a directory's size
    strcpy(relPath, path); 

	while ((curFile=readdir(curDir)) != NULL) { // takes every file in the directory
        if (!strcmp(".", curFile->d_name) || !strcmp("..", curFile->d_name))
            continue;
		if (curFile->d_type == DT_DIR) { // If the file is a directory
			strcat(strcat(relPath, "/"), curFile->d_name); 
			local_size = postOrderApply(relPath, pathfun);
			if (local_size != -1)
				printf("%d	%s\n", local_size / 1024, relPath);
			if (isOption == 1 && local_size != -1)
				file_size += local_size;
		}
		else { // is any file but a directory
			strcat(strcat(relPath, "/"), curFile->d_name);
			int fileSize = pathfun(relPath);
			if (fileSize == -1)
				printf("Special file %s\n", curFile->d_name);
			if (fileSize != -1 && fileSize != -2)
				file_size += pathfun(relPath);
		}
		size_t remChar = (strlen(relPath) - strlen(curFile->d_name) - 1);
		memmove(relPath, relPath, remChar);
		relPath[remChar] = '\0'; 	
	}	
	closedir(curDir);
	return file_size;
}



// Checks if the number of given command line arguments are valid. Terminates if not.
void argcControl(int argc) {
	if ((argc != 2) && (argc != 3)) {
		printf("2 or 3 argument is required.\n./buNeDu [-z] path_name\n");
		exit(EXIT_FAILURE);
	}
	if (argc == 3)
		isOption = 1;
}



// Checks if given command line arguments are valid. Terminates if not. If does, return path of the given directory as a command line argument.
char* argvControl(int argc, char **argv) { 
	if (argc == 2) {
		char *path = *(argv + 1);
		DIR *retVal = opendir(path);
		if (retVal == NULL) {
			printf("Wrong path name.\n./buNeDu [-z] path_name\n");
			exit(EXIT_FAILURE);
		}
		closedir(retVal);
		return path;
	}
	else {	// argc == 3
		char *path = *(argv + 2);
		char *option = *(argv + 1);
		DIR *retVal = opendir(path);
		if (retVal == NULL) {
			printf("Wrong path name.\n./buNeDu [-z] path_name\n");
			exit(EXIT_FAILURE);
		}	
		if (strcmp(option, "-z")) {
			printf("[-z] option needs to be passed.\n./buNeDu [-z] path_name\n"); 
			exit(EXIT_FAILURE);
		}
		closedir(retVal);
		return path;
	}
	
	return NULL;
}



// Returns # of bytes in a given file if there no is any error, returns some negative values otherwise.
int sizepathfun (char *path) {
        struct stat attrs;  
	if (lstat(path,&attrs) < 0) 
		return -2;
	if (!S_ISREG(attrs.st_mode) && !S_ISDIR(attrs.st_mode)) {
		return -1;
	}	
	if (lstat(path, &attrs) >= 0)
		return attrs.st_size; 
	else 
		return -2;
}
