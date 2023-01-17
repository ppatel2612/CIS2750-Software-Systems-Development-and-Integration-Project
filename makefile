#	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
#	Student Number: 1140832		Date: 2023-01-31
CC = gcc
CFLAGS = -fpic -std=c99 -Wall -pedantic

all: libmol.so

libmol.so: mol.o
	$(CC) -shared -o $@ $^

mol.o: mol.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o libmol.so