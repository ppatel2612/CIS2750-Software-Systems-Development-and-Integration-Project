CC = clang
CFLAGS = -Wall -std=c99 -pedantic

libmol.so: mol.o
	$(CC) mol.o -shared -o libmol.so -lm

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o

clean:
	rm -f *.o *.so run

