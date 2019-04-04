#include    <stdio.h>
#include    <unistd.h>



int main(int argc, char **argv) {
    if (argc == 2) {
        int notSuccessful = chdir(argv[1]);
        if (notSuccessful) 
            fprintf(stderr, "The path couldn't be found.\n");
        else {
            char name[1024] = { 0 };
            printf("%s\n", getcwd(name, 100));
        }

    } 
    else 
        fprintf(stderr, "More arguments than intended.\n");
}
