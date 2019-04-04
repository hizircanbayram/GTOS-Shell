#include    <stdio.h>
#include    <unistd.h>



int main(int argc, char **argv) {
   char pwdName[1024] = { 0 };
   getcwd(pwdName, 1024); 
   printf("%s\n", pwdName);
}
