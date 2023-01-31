#include "mol.h"

void atomset(atom *atom, char element[3], double *x, double *y, double *z)
{
    /*
     *  Copy the values pointed to by the arguments into the atom stored at atom.
     */
    strncpy(atom->element, element, 3);
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;
}

void atomget(atom *atom, char element[3], double *x, double *y, double *z)
{
    /*
    * Copy the values in the atom stored at atom to the locations pointed to by element, x, y, and z
    */
    strncpy(element, atom->element, 3);
    *x = atom->x;
    *y = atom->y;
    *z = atom->z;
}

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs)
{
    /*
    *  Copy the values a1, a2 and epairs into the corresponding structure attributes in bond
    */
    bond->a1 = a1;
    bond->a2 = a2;
    bond->epairs = epairs;
}

void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs)
{
    /*
    *  Copy the values a1, a2 and epairs into the corresponding structure attributes in bond
    */
    *a1 = bond->a1;
    *a2 = bond->a2;
    *epairs = bond->epairs;
}

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max)
{
    molecule *mol = malloc(sizeof(molecule));       // Allocate memory for atom 'molecule' structure
    if (mol == NULL)
    {      // Check if memory allocation failed
        return NULL;
    }

    mol->atom_max = atom_max;       // Set the value of atom_max in the structure to the value specified in the argument
    mol->atom_no = 0;       // Set the value of atom_no in the structure to zero

    mol->atoms = malloc(sizeof(atom) * atom_max);       // Allocate memory for array 'atoms' to hold atom_max atoms
    if (mol->atoms == NULL)
    {      // Check if memory allocation failed
        return NULL;
    }
    memset(mol->atoms, 0, sizeof(atom) * atom_max);

    mol->atom_ptrs = malloc(sizeof(atom *) * atom_max);        // Allocate memory for array 'atom_ptrs'
    if (mol->atom_ptrs == NULL)
    {      // Check if memory allocation failed
        return NULL;       // malloc failed
    }
    memset(mol->atom_ptrs, 0, sizeof(atom *) * atom_max);

    mol->bond_max = bond_max;       // Set the value of bond_max in the structure to the value specified in the argument
    mol->bond_no = 0;       // Set the value of bond_no in the structure to zero

    mol->bonds = malloc(sizeof(bond) * bond_max);       // Allocate memory for array 'bonds' to hold bond_max bonds
    if (mol->bonds == NULL)
    {       // Check if memory allocation failed
        return NULL;
    }
    memset(mol->bonds, 0, sizeof(bond) * bond_max);

    mol->bond_ptrs = malloc(sizeof(bond *) * bond_max);        // Allocates memory for array 'bond_ ptrs' NOTE: its **
    if (mol->bond_ptrs == NULL)
    {       // Check if memory allocation failed
        return NULL;
    }
    memset(mol->bond_ptrs, 0, sizeof(bond *) * bond_max);

    return mol;     // Returns the address of the malloced memory for the molecule
}

molecule *molcopy(molecule *src)
{
    // Allocate memory for the new molecule
    molecule *new_mol = molmalloc(src->atom_max, src->bond_max);
    if (new_mol == NULL)
    {      // Check if memory allocation failed
        return NULL;
    }

    // Copy atoms and bonds from src to new_mol using molappend_atom and molappend_bond
    for (int i = 0; i < src->atom_no; i++)
    {
        molappend_atom(new_mol, &src->atoms[i]);
    }
    for (int i = 0; i < src->bond_no; i++)
    {
        molappend_bond(new_mol, &src->bonds[i]);
    }

    // Reassign atom pointers in bonds to point to new atoms
    for (int i = 0; i < new_mol->bond_no; i++)
    {
        bond *b = new_mol->bonds + i;
        for (int j = 0; j < src->atom_no; j++)
        {
            atom *a = src->atoms + j;
            if (b->a1 == a)
            {
                b->a1 = new_mol->atoms + j;
            }
            if (b->a2 == a)
            {
                b->a2 = new_mol->atoms + j;
            }
        }
    }

    return new_mol;
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

void molappend_atom(molecule *molecule, atom *atom)
{
    if( molecule->atom_no == molecule->atom_max) {      // Checks for available space in molecule for new atom
        molecule->atom_max *= 2;
        if( molecule->atom_max == 0 ) {
            molecule->atom_max = 1;
        }

        // Reallocate memory for the new atoms || Exits if memory allocation fails
        molecule->atoms = realloc( molecule->atoms, molecule->atom_max * (sizeof *molecule->atoms) );       // Gets more memory for new atom
        if (molecule->atoms == NULL) {
            printf("Error: realloc failed to allocate memory for atoms\n");
            exit(1);
        }
        molecule->atom_ptrs = realloc( molecule->atom_ptrs, molecule->atom_max * (sizeof *molecule->atom_ptrs) );
        if (molecule->atom_ptrs == NULL) {
            printf("Error: realloc failed to allocate memory for atom_ptrs\n");
            exit(1);
        }
        // reassign the atom_ptrs to point to the new location of the atoms struct
        for (int i = 0; i < molecule->atom_no; i++) {
            molecule->atom_ptrs[i] = &molecule->atoms[i];
        }
    }
    // Assign new atom values from given src
    molecule->atoms[molecule->atom_no] = *atom;
    molecule->atom_ptrs[molecule->atom_no] = &molecule->atoms[molecule->atom_no];
    molecule->atom_no++;
}

void molappend_bond(molecule *molecule, bond *bond)
{
    if( molecule->bond_no >= molecule->bond_max) {      // Checks for available space in molecule for new bond
        molecule->bond_max *= 2;
        if( molecule->bond_max == 0 ) {
            molecule->bond_max = 1;
        }

        // Reallocate memory for new bonds || Exits if memory allocation fails
        molecule->bonds = realloc( molecule->bonds, molecule->bond_max * (sizeof *molecule->bonds) );
        if (molecule->bonds == NULL) {
            printf("Error: realloc failed to allocate memory for bonds\n");
            exit(1);
        }
        molecule->bond_ptrs = realloc( molecule->bond_ptrs, molecule->bond_max * (sizeof *molecule->bond_ptrs) );
        if (molecule->bond_ptrs == NULL) {
            printf("Error: realloc failed to allocate memory for bond_ptrs\n");
            exit(1);
        }
        // reassign the bond_ptrs to point to the new location of the bonds struct
        for (int i = 0; i < molecule->bond_no; i++) {
            molecule->bond_ptrs[i] = &molecule->bonds[i];
        }
    }
    // Assign new atom values from given src
    molecule->bonds[molecule->bond_no] = *bond;
    molecule->bond_ptrs[molecule->bond_no] = &molecule->bonds[molecule->bond_no];
    molecule->bond_no++;
}

void molsort(molecule *molecule)
{
    qsort(molecule->atom_ptrs, molecule->atom_no, sizeof(atom *), cmp_atoms);
    qsort(molecule->bond_ptrs, molecule->bond_no, sizeof(bond *), cmp_bonds);
}

void xrotation(xform_matrix xform_matrix, unsigned short deg)
{
    double rad = deg * M_PI / 180.0; // convert degrees to rad
    double sine = sin(rad);
    double cosine = cos(rad);
    xform_matrix[0][0] = 1.0;       // Uses values from affine matrix transformation
    xform_matrix[0][1] = 0.0;
    xform_matrix[0][2] = 0.0;
    xform_matrix[1][0] = 0.0;
    xform_matrix[1][1] = cosine;
    xform_matrix[1][2] = -sine;
    xform_matrix[2][0] = 0.0;
    xform_matrix[2][1] = sine;
    xform_matrix[2][2] = cosine;
}

void yrotation(xform_matrix xform_matrix, unsigned short deg)
{
    double rad = (deg * M_PI) / 180; // convert deg to rad
    double sine = sin(rad);
    double cosine = cos(rad);

    xform_matrix[0][0] = cosine;       // Uses values from affine matrix transformation
    xform_matrix[0][1] = 0;
    xform_matrix[0][2] = sine;
    xform_matrix[1][0] = 0;
    xform_matrix[1][1] = 1;
    xform_matrix[1][2] = 0;
    xform_matrix[2][0] = -sine;
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = cosine;
}

void zrotation(xform_matrix xform_matrix, unsigned short deg)
{
    double rad = (deg * M_PI) / 180; // convert deg to rad
    double sine = sin(rad);
    double cosine = cos(rad);

    xform_matrix[0][0] = cosine;       // Uses values from affine matrix transformation
    xform_matrix[0][1] = -sine;
    xform_matrix[0][2] = 0;
    xform_matrix[1][0] = sine;
    xform_matrix[1][1] = cosine;
    xform_matrix[1][2] = 0;
    xform_matrix[2][0] = 0;
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = 1;
}

void mol_xform(molecule *molecule, xform_matrix matrix)
{
    for (int i = 0; i < molecule->atom_no; i++)
    {
        // Iterates through all atoms in the molecule
        double x = molecule->atoms[i].x;
        double y = molecule->atoms[i].y;
        double z = molecule->atoms[i].z;

        // Vector multiplication using provided matrix
        molecule->atoms[i].x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
        molecule->atoms[i].y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
        molecule->atoms[i].z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;
    }
}

int cmp_atoms(const void *a, const void *b)
{
    atom **A = (atom **) a;
    atom **B = (atom **) b;
    return ((*A)->z > (*B)->z) - ((*A)->z < (*B)->z);
}

int cmp_bonds(const void *a, const void *b)
{
	bond **A = (bond **) a;
    bond **B = (bond **) b;
    double za = ((*A)->a1->z + (*A)->a2->z) / 2;        // Computes avg
    double zb = ((*B)->a1->z + (*B)->a2->z) / 2;
    return (za > zb) - (za < zb);
}


