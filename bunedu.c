#include	"bunedu.h"



int isOption = 0;

// 1 : ard_ind
int main(int argc, char **argv) {	
    int pipeArr[2];
    int arg_ind = 1;
    int arg_limit = 2;
    if (!strcmp("-z", argv[1])) {
        arg_ind = 2;
        arg_limit += 1;
    }
    if (BUNEDU_ONE_ARG(argc)) {
        postOrderApply(argv[arg_ind], sizepathfun, pipeArr, NULL, argc, argv, NULL);
    }
    else if (BUNEDU_REDIRECT(argc)) {
        if (!strcmp(">", argv[arg_ind + 1])) {
            printf("(%s) , (%s) \n", argv[arg_ind], argv[arg_ind + 2]);
            FILE *write_fp = fopen(argv[arg_ind + 2], "w");
            if (!write_fp) {
                fprintf(stderr, "BUNEDU | Output redirecting file %s couldn't be opened for some reason.\n", argv[arg_ind + 2]);
                exit(EXIT_FAILURE);
            }
            postOrderApply(argv[arg_ind], sizepathfun, pipeArr, argv[arg_ind + 2], argc, argv, write_fp);
        }
        else if (!strcmp("<", argv[arg_ind])) {
            // ilk parametre dosya icerigi(arg_ind + 1) olacak, redirectPath NULL olacak
            FILE *redirect_fp = fopen(argv[arg_ind + 1], "r");
            if (!redirect_fp) {
                fprintf(stderr, "BUNEDU | Input redirecting file couldn't be opened for some reason.\n");
                exit(EXIT_FAILURE);
            }
            char *line = NULL;
            int redirect_flag = 0;
            size_t redirect_len = getline(&line, &redirect_flag, redirect_fp);
            line[redirect_len - 1] = '\0';
            fprintf(redirect_fp, "%s", line);
            postOrderApply(line, sizepathfun, pipeArr, NULL, argc, argv, NULL);
        }
        else if (!strcmp("|", argv[arg_ind + 1])) {

        }
        else {
            fprintf(stderr, "BUNEDU | Undefined operation.\n");
            exit(EXIT_FAILURE);
        }
    }    
    else {
        fprintf(stderr, "BUNEDU | Invalid number of arguments are supplied.\n");
    }

	return EXIT_SUCCESS;
}



void postOrderApply(char *path, int pathfun (char *path1), const int *pipeArr, const char *redirectFileName, int argc, char **argv, FILE *write_fp) {
	argcControl(argc, argv); // checks if the number of given command line arguments are valid.
	argvControl(argc, argv); // checks if the given command line arguments are valid.
	unsigned int retVal = postOrderApplyPrivate(path, sizepathfun, pipeArr, redirectFileName, write_fp);	
    if (!strcmp("-z", argv[1]))  // -z option is given
		printf("%d	%s\n", retVal / 1024, *(argv + 2)); 
	else  // -z option is given
		printf("%d	%s\n", retVal / 1024, *(argv + 1)); 
}



// Traverses the tree in a post order way so that all directories can be computed in some way. Susm up all the ordinary files, displays their values but specific files.
int postOrderApplyPrivate(char *path, int pathfun (char *path1), const int *pipeArr, const char *redirectFileName, FILE *write_fp) {
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
			local_size = postOrderApplyPrivate(relPath, pathfun, pipeArr, redirectFileName, write_fp);
			if (local_size != -1) {
                if (write_fp)
				    fprintf(write_fp, "%d	%s\n", local_size / 1024, relPath);
                else
				    printf("%d	%s\n", local_size / 1024, relPath);
            }
			if (isOption == 1 && local_size != -1)
				file_size += local_size;
		}
		else { // is any file but a directory
			strcat(strcat(relPath, "/"), curFile->d_name);
			int fileSize = pathfun(relPath);
			if (fileSize == -1) {
                if (write_fp)
				    fprintf(write_fp, "Special file %s\n", curFile->d_name);
                else
				    printf("Special file %s\n", curFile->d_name);
            }
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
void argcControl(int argc, char **argv) {
    if (!strcmp("-z", argv[1])) {
	    if ((argc != 3) && (argc != 4) && (argc != 5)) {
		    printf("3 or 4 or 5 argument is required.\n./buNeDu [-z] path_name\n");
		    exit(EXIT_FAILURE);
	    }
		isOption = 1;
    }
    else {
	    if ((argc != 2) && (argc != 3) && (argc != 4)) {
		    printf("2 or 3 or 4 argument is required.\n./buNeDu [-z] path_name\n");
		    exit(EXIT_FAILURE);
	    }
    }
}



// Checks if given command line arguments are valid. Terminates if not. If does, return path of the given directory as a command line argument.
char* argvControl(int argc, char **argv) { 
    if (strcmp("-z", argv[1]))  { // if the option is not given
        if (!strcmp("<", argv[1])) { // input redirecting

        }
        else { // otherwise
		    char *path = *(argv + 1);
		    DIR *retVal = opendir(path);
		    if (retVal == NULL) {
			    printf("Wrong path name.\n./buNeDu [-z] path_name\n");
			    exit(EXIT_FAILURE);
		    }
		    closedir(retVal);
		    return path;
        }
        return NULL;
	}
	else {	// if the option is given
        if (!strcmp("<", argv[2])) { // output redirecting

        }
        else { // otherwise
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
