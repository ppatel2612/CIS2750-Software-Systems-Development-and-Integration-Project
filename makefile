#	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
#	Student Number: 1140832		Date: 2023-01-31
CC = gcc
CFLAGS = -fpic -std=c99 -Wall -pedantic -lm

all: libmol.so test1

libmol.so: mol.o
	$(CC) -shared -o $@ $^ -lm

mol.o: mol.c
	$(CC) $(CFLAGS) -c $<

test1.o: test1.c mol.h
	$(CC) $(CFLAGS) -c test1.c test1.o

test1: test1.c libmol.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmol -lm

clean:
	rm -f *.o *.so test1
