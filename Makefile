compile: all

all: shell.o cat.o bunedu.o lsf.o pwd.o wc.o

bunedu.o: bunedu.c
	gcc -c bunedu.c -o bunedu.o -Wall
	gcc bunedu.o -o bunedu
	rm bunedu.o

cat.o: cat.c
	gcc -c cat.c -o cat.o -Wall
	gcc cat.o -o cat
	rm cat.o

lsf.o: lsf.c
	gcc -c lsf.c -o lsf.o -Wall
	gcc lsf.o -o lsf
	rm lsf.o

pwd.o: pwd.c
	gcc -c pwd.c -o pwd.o -Wall
	gcc pwd.o -o pwd
	rm pwd.o

shell.o: shell.c
	gcc -c -std=c99 shell.c -o shell.o -Wall
	gcc shell.o -o gtushell
	rm shell.o

wc.o: wc.c
	gcc -c wc.c -o wc.o -Wall
	gcc wc.o -o wc
	rm wc.o
