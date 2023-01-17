//	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
//	Student Number: 1140832		Date: 2023-01-31
#include "mol.h"

void atomset(atom *atom, char element[3], double *x, double *y, double *z)
{
	strncpy(atom->element, element, 3);
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;
}

void atomget(atom *atom, char element[3], double *x, double *y, double *z)
{
	strncpy(element, atom->element, 3);
    *x = atom->x;
    *y = atom->y;
    *z = atom->z;
}

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs)
{
}

void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs)
{
}

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max)
{
	molecule *mol = (molecule *)malloc(sizeof(molecule));
    if (mol == NULL) {
        return NULL; // malloc failed
    }
    mol->atom_max = atom_max;
    mol->atom_no = 0;
    mol->atoms = (atom *)malloc(sizeof(atom) * atom_max);
    if (mol->atoms == NULL) {
        free(mol);
        return NULL; // malloc failed
    }
    mol->atom_ptrs = (atom **)malloc(sizeof(atom *) * atom_max);
    if (mol->atom_ptrs == NULL) {
        free(mol->atoms);
        free(mol);
        return NULL; // malloc failed
    }

    mol->bond_max = bond_max;
    mol->bond_no = 0;
    mol->bonds = (bond *)malloc(sizeof(bond) * bond_max);
    if (mol->bonds == NULL) {
        free(mol->atoms);
        free(mol->atom_ptrs);
        free(mol);
        return NULL; // malloc failed
    }
    mol->bond_ptrs = (bond **)malloc(sizeof(bond *) * bond_max);
    if (mol->bond_ptrs == NULL) {
        free(mol->atoms);
        free(mol->atom_ptrs);
        free(mol->bonds);
        free(mol);
        return NULL; // malloc failed
    }

    return mol;
}
