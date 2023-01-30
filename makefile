#	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
#	Student Number: 1140832		Date: 2023-01-31
CC = clang
CFLAGS = -Wall -std=c99 -pedantic

all: run

clean:
	rm -f *.o *.so run

libmol.so: mol.o
	$(CC) mol.o -shared -o libmol.so -lm

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o

test6.o: test6.c mol.h
	$(CC) $(CFLAGS) -c test6.c -o test6.o

run: test6.o libmol.so
	$(CC) test6.o -L. -lmol -o run -lm
