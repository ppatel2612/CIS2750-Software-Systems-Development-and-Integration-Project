#include "mol.h"

void atomset(atom *atom, char element[3], double *x, double *y, double *z)
{
}

void atomget(atom *atom, char element[3], double *x, double *y, double *z)
{
}

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs)
{
}

void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs)
{
}

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max)
{
}
