Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
Student Number: 1140832		Date: 2023-01-31
------------------------------------------------------------------------
To Run this program:
	Ensure that the shared library can be found by the compiler.
		In no machine, I used the terminal commands:
			LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/patprat2612/CIS2750W23/A1/libmol.so
			export LD_LIBRARY_PATH
		This would ensure that the compiler can find the shared library as we provided the file path to the shared library.
	Next, in terminal, use the 'make all' command to create the necessary targets and files to run the program.
------------------------------------------------------------------------
This is A1 for CIS2750 Winter 2023. It consists of 3 files; mol.c mol.h and makfile.

MOL.H:	Contains all function prototypes, typedefs and structure definitions that are used in the libmol.so library.

MOL.C:	Contains all the functions codes that are used in the libmol.so library.

MAKEFILE:	Contains the code to compile and create the necessary files to run the program. It contains the targets; mol.o libmol.so and clean. When ran successfully, it should link the shared library (libmol.so) so that the compiler can access the function code and create the executable file.