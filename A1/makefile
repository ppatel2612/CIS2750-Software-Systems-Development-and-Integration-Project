CC = clang
CFLAGS = -Wall -std=c99 -pedantic
TESTFILE = test6

all: run

libmol.so: mol.o
	$(CC) mol.o -shared -o libmol.so -lm

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o
	
$(TestFile).o: $(TestFile).c mol.h
	$(CC) $(CFLAGS) -c $(TestFile).c -o $(TestFile).o

run: $(TestFile).o libmol.so
	$(CC) $(TestFile).o -L. -lmol -o run -lm
clean:
	rm -f *.o *.so run
	
