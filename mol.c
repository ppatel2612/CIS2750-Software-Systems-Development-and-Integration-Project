//	Name: Pratham Patel			Course: CIS2750 		ID: ppatel36
//	Student Number: 1140832		Date: 2023-01-31
#include "mol.h"

void atomset(atom *atom, char element[3], double *x, double *y, double *z)
{
    /*  
     *  Copy the values pointed to by the arguments into the atom stored at atom.
     */
	strncpy(atom->element, element, 3);     // Uses strncpy to copy over the string as it specifies a maximum length
    atom->x = *x;       // Copy over the values POINTED TO by arguments
    atom->y = *y;       // """
    atom->z = *z;       // """
}

void atomget(atom *atom, char element[3], double *x, double *y, double *z)
{
    /*
    * Copy the values in the atom stored at atom to the locations pointed to by element, x, y, and z
    */
	strncpy(element, atom->element, 3);     // Uses strncpy to copy over the string as it specifies a maximum length
    *x = atom->x;       // Copy over the values POINTED TO by the elements
    *y = atom->y;       // """
    *z = atom->z;       // """
}

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs)
{
    /*
    *  Copy the values a1, a2 and epairs into the corresponding structure attributes in bond
    */
    bond->a1 = a1;      // Not copying the structs just the addresses
    bond->a2 = a2;
    bond->epairs = epairs;
}

void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs)
{
    /*
    *  Copy the values a1, a2 and epairs into the corresponding structure attributes in bond
    */
    *a1 = bond->a1;     // Not copying the structs just the addresses
    *a2 = bond->a2;
    *epairs = bond->epairs;
}

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max)
{
	molecule *mol = (molecule *)malloc(sizeof(molecule));       // Allocate memory for a 'molecule' structure
    if (mol == NULL) {      // Check if memory allocation failed
        return NULL;        // malloc failed
    }

    mol->atom_max = atom_max;       // Set the value of atom_max in the structure to the value specified in the argument
    mol->atom_no = 0;       // Set the value of atom_no in the structure to zero
    
    mol->atoms = (atom *)malloc(sizeof(atom) * atom_max);       // Allocate memory for array 'atoms' to hold atom_max atoms
    if (mol->atoms == NULL) {      // Check if memory allocation failed
        free(mol);      // Frees mol structure to ensure no memory errors
        return NULL;        // malloc failed
    }

    mol->atom_ptrs = (atom **)malloc(sizeof(atom *) * atom_max);        // Allocate memory for array 'atom_ptrs'
    if (mol->atom_ptrs == NULL) {      // Check if memory allocation failed
        free(mol->atoms);       // Frees array in struct before freeing struct to ensure all memory is freed 
        free(mol);      // Frees mol structure to ensure no memory errors
        return NULL;        // malloc failed
    }

    mol->bond_max = bond_max;       // Set the value of bond_max in the structure to the value specified in the argument
    mol->bond_no = 0;       // Set the value of bond_no in the structure to zero

    mol->bonds = (bond *)malloc(sizeof(bond) * bond_max);       // Allocate memory for array 'bonds' to hold bond_max bonds
    if (mol->bonds == NULL) {       // Check if memory allocation failed
        free(mol->atoms);       // Frees all allocated memory in the structure to ensure no memory errors
        free(mol->atom_ptrs);   // "'"
        free(mol);              // "'"
        return NULL;        // malloc failed
    }
    mol->bond_ptrs = (bond **)malloc(sizeof(bond *) * bond_max);        // Allocates memory for array 'bond_ ptrs' NOTE: its **
    if (mol->bond_ptrs == NULL) {       // Check if memory allocation failed
        free(mol->atoms);       // Frees all allocated memory in the structure to ensure no memory errors
        free(mol->atom_ptrs);
        free(mol->bonds);
        free(mol);
        return NULL;        // malloc failed
    }

    return mol;     // Returns the address of the malloced memory for the molecule
}

molecule *molcopy(molecule *src)
{
	molecule *copied_mol = molmalloc(src->atom_max, src->bond_max);     // Allocates memory for the new struct by calling molmalloc function with the src values for atom_max and bond_max and bond_max
    
    if (copied_mol == NULL) {       // If memory allocation failed
        return NULL;
    }

    // Copies the values from src to copied_mol structure
    // Note that enough memory is already allocated as the new structure is the same size as the src structure
    memcpy(copied_mol->atoms, src->atoms, sizeof(atom) * src->atom_max);
    memcpy(copied_mol->atom_ptrs, src->atom_ptrs, sizeof(atom *) * src->atom_max);
    memcpy(copied_mol->bonds, src->bonds, sizeof(bond) * src->bond_max);
    memcpy(copied_mol->bond_ptrs, src->bond_ptrs, sizeof(bond *) * src->bond_max);

    copied_mol->atom_no = src->atom_no;
    copied_mol->bond_no = src->bond_no;

    return copied_mol;      // Returns the address of the copied structure's memory
}

void molfree(molecule *ptr)
{
    /*
    * Frees all allocated memory within the structure before freeing the ptr itself
    */
    free(ptr->atoms);
    free(ptr->atom_ptrs);
    free(ptr->bonds);
    free(ptr->bond_ptrs);
    free(ptr);
}
