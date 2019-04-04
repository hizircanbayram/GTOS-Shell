#include    <stdio.h>


int main() {

	printf("- lsf : This command lists file type (R for regular file, S for non-regular(special) file), access rights (int the form of rwxr-xr-x, just like actual ls), file size(bytes) and file name of all files (not directories) in the present working directory. It doesn’t take any argument. Does not list any directory.\n\
- pwd : This command prints the path of present working directory.\n\
- cd : This command changes the present working directory to the location provided as argument.\n\
- help : This command prints the list of supported commands.\n\
- cat : This command prints on standard output the contents of the file provided to it as argument or from standard input. The file can be on any directory on the system. (example, cat file.txt )(example2, pwd | cat )\n\
- wc : This command prints on standard output the number of lines in the file provided to it as argument or the string coming from standard input until EOF character (example, Input: wc file.txt Output:55) (example2, Input: lsf | wc Output: 5 (there are 5 files in current directory so output of lsf has 5 lines)).\n\
- bunedu : This command prints the size of subdirectories of a given directory the file path argument of bunedu can also come from standard input.\n\
- exit : It will exit the shell.\n");

}
