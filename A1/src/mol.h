#ifndef __PPATEL36__A1H__
#define __PPATEL36__A1H__

#define M_PI 3.14159265358979323846

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct atom						//atom defines a structure that represents an atom and its position in 3D space
{
	char element[3];						//element is a null-terminated string representing the name of the element (e.g. "Na" for sodium)
	double x, y, z;							//Double precision floating point values describing the position in Angstroms of the atom relative to a common origin for a molecule
} atom;

typedef struct bond						//bond defines a structure that represents a co-valent bond between two atoms
{
	atom *a1, *a2;							//a1 and a2 are pointers to the two atoms in the co-valent bond (Don't need to free a1 and a2 since they are stored  elsewhere)
	unsigned char epairs;					//epairs is the number of electron pairs in the co-valent bond (i.e. epairs = 2 represents a double bond)
} bond;

typedef struct molecule					//molecule represents a molecule which consists of zero or more atoms, and zero or more bonds.
{
	unsigned short atom_max, atom_no;		//atom_max is a non-negative integer that records the dimensionality of an array pointed to by atoms
	atom *atoms, **atom_ptrs;				//atom_no is the number of atoms currently stored in the array atoms || atom_max >= atom_no
	unsigned short bond_max, bond_no;		//bond_max is a non-negative integer that records the dimensionality of an array pointed to by bonds
	bond *bonds, **bond_ptrs;				//bond_no is the number of bonds currently stored in the array bonds || bond_max >= bond_no
} molecule;								//atom_ptrs and bond_ptrs are arrays of pointers. Their dimensionalities will correspond to the atoms and bonds arrays, respectively
//These pointers in these pointer arrays will be initialized to point to their corresponding structures. E.g. atom_ptrs[0] will point to atoms[0].

typedef double xform_matrix[3][3];		//xform matrix represents a 3D affine transformation matrix.

void atomset( atom *atom, char element[3], double *x, double *y, double *z );		//Copy values pointed to by element, x, y, and z into the atom stored at atom
void atomget( atom *atom, char element[3], double *x, double *y, double *z );		//Copy values in the atom stored at atom to the locations pointed to by element, x, y, and z
void bondset( bond *bond, atom *a1, atom *a2, unsigned char epairs );				//Copy the values a1, a2 and epairs into the corresponding structure attributes in bond (ONLY ADDRESSES)
void bondget( bond *bond, atom **a1, atom **a2, unsigned char *epairs );			//Copy the structure attributes in bond to the corresponding arguments: a1, a2 and epairs (ONLY ADDRESSES)
molecule *molmalloc( unsigned short atom_max, unsigned short bond_max );			//Return the address of a malloced area of memory large enough to hold a molecule
molecule *molcopy( molecule *src );													//Return the address of	a malloced area of memory large enough to hold the src object
void molfree( molecule *ptr );														//Free the memory associated with molecule pointed to by ptr
void molappend_atom( molecule *molecule, atom *atom );								//Copy the data pointed to by atom to the first "empty" atom in atoms in the molecule pointed to by molecule
void molappend_bond( molecule *molecule, bond *bond );								//Copy the data pointed to by bond to the first "empty" bond in bond in the molecule pointed to by molecule
void molsort( molecule *molecule );													//Sort the atom_ptrs array in order of increasing z value | sort bond_ptrs array in order of z values
void xrotation( xform_matrix xform_matrix, unsigned short deg );					//Allocate, compute and return an affine transformation matrix corresponding to a rotation of deg degrees around the x axis
void yrotation( xform_matrix xform_matrix, unsigned short deg );					//Allocate, compute and return an affine transformation matrix corresponding to a rotation of deg degrees around the y axis
void zrotation( xform_matrix xform_matrix, unsigned short deg );					//Allocate, compute and return an affine transformation matrix corresponding to a rotation of deg degrees around the z axis
void mol_xform( molecule *molecule, xform_matrix matrix );							//Apply the transformation matrix to all the atoms of the molecule by performing a vector matrix multiplication on the x, y, and z coordinates

int cmp_atoms(const void *a, const void *b);										//Helper function for sorting atom pointers
int cmp_bonds(const void *a, const void *b);										//Helper function for sorting bond pointers

#endif

