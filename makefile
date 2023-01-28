#	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
#	Student Number: 1140832		Date: 2023-01-31
CC = gcc
CFLAGS = -lm -Wall -Werror -g -std=c99 -pedantic

all: run

clean:
	rm -f *.o *.so run

libmol.so: mol.o
	$(CC) mol.o -lm -shared -g -o libmol.so

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o

test1.o: test1.c mol.h
	$(CC) $(CFLAGS) -c test1.c -o test1.o

run: test1.o libmol.so
	$(CC) test1.o -L. -lmol -g -o run

