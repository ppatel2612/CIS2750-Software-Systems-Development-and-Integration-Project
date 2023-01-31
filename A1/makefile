CC = clang
CFLAGS = -Wall -std=c99 -pedantic
TESTFILE = test6

all: run

libmol.so: mol.o
	$(CC) mol.o -shared -o libmol.so -lm

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o
	
$(TESTFILE).o: $(TESTFILE).c mol.h
	$(CC) $(CFLAGS) -c $(TESTFILE).c -o $(TESTFILE).o

run: $(TESTFILE).o libmol.so
	$(CC) $(TESTFILE).o -L. -lmol -o run -lm
clean:
	rm -f *.o *.so run
	
