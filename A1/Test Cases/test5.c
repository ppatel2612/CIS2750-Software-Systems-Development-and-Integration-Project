#include "mol.h"

#ifndef STDIO_H
#include <stdio.h>
#endif // !STDIO_H

void display_mol(molecule *molecule)
{
  /* display the molecule */

  /* atoms */
  printf("atom_max: %hu, atom_no: %hu\n",
         molecule->atom_max, molecule->atom_no);
  for (int i = 0; i < molecule->atom_no; i++)
  {
    char name[3];
    double x, y, z;
    atom *atom_ptr;

    atom_ptr = molecule->atoms + i;

    atomget(atom_ptr, name, &x, &y, &z);
    printf("atom[%d] %p %-2s: %lf %lf %lf\n",
           i, (void *)atom_ptr, name, x, y, z);
  }

  for (int i = 0; i < molecule->atom_no; i++)
  {
    atom *atom_ptr = molecule->atom_ptrs[i];
    char name[3];
    double x, y, z;
    atomget(atom_ptr, name, &x, &y, &z);

    printf("atom_ptrs[%d] %p %-2s: %lf %lf %lf\n",
           i, (void *)(molecule->atom_ptrs[i]), name, x, y, z);
  }

  /* bonds */
  printf("bond_max: %hu, bond_no: %hu\n",
         molecule->bond_max, molecule->bond_no);
  for (int i = 0; i < molecule->bond_no; i++)
  {
    atom *a1, *a2;
    unsigned char epairs;
    bond *bond_ptr;

    bond_ptr = molecule->bonds + i;
    bondget(bond_ptr, &a1, &a2, &epairs);
    printf("bond[%d] %p: %p %p %hhu\n",
           i, (void *)bond_ptr, (void *)a1, (void *)a2, epairs);
  }

  for (int i = 0; i < molecule->bond_no; i++)
  {
    printf("bond_ptrs[%d]: %p\n", i, (void *)(molecule->bond_ptrs[i]));
  }
}

void display_bonds(molecule *molecule)
{
  /* bonds */
  printf("bond_max: %hu, bond_no: %hu\n",
         molecule->bond_max, molecule->bond_no);
  for (int i = 0; i < molecule->bond_no; i++)
  {
    atom *a1, *a2;
    unsigned char epairs;
    bond *bond_ptr;

    bond_ptr = molecule->bonds + i;
    bondget(bond_ptr, &a1, &a2, &epairs);
    printf("bond[%d] %p: %p %p %hhu\n",
           i, (void *)bond_ptr, (void *)a1, (void *)a2, epairs);
  }

  for (int i = 0; i < molecule->bond_no; i++)
  {
    atom *a1, *a2;
    unsigned char epairs;

    bondget(molecule->bond_ptrs[i], &a1, &a2, &epairs);

    printf("bond_ptrs[%d]: %p %p %p %hhu\n", i, (void *)(molecule->bond_ptrs[i]), (void *)a1, (void *)a2, epairs);

    // atoms
    char name[3];
    double x, y, z;
    // a1
    atomget(molecule->bond_ptrs[i]->a1, name, &x, &y, &z);
    printf("\t a1: %-2s: %lf %lf %lf\n", name, x, y, z);
    // a2
    atomget(molecule->bond_ptrs[i]->a2, name, &x, &y, &z);
    printf("\t a2: %-2s: %lf %lf %lf\n", name, x, y, z);
  }
}

void display_matrix(xform_matrix matrix)
{
  printf("\nMatrix: \n");
  for (int i = 0; i < 3; i++)
  {
    for (int k = 0; k < 3; k++)
    {
      printf("\t%lf", matrix[i][k]);
    }
    printf("\n");
  }
}

void testAtomSet(atom *a1, atom *a2, atom *a3)
{
  double x, y, z;
  /* set the atoms */
  x = 2.5369;
  y = -0.1550;
  z = 1.0000;
  // z = 0.0000;
  atomset(a1, "O", &x, &y, &z);

  x = 3.0739;
  y = 0.1550;
  z = 0.5000;
  atomset(a2, "H", &x, &y, &z);

  x = 2.0000;
  y = 0.1550;
  z = 1.5000;
  // z = 0.0000;
  atomset(a3, "H", &x, &y, &z);
}

void testMolappend_atom(molecule *molecule, atom *a1, atom *a2, atom *a3)
{
  /* add atoms to molecule */
  molappend_atom(molecule, a1);
  molappend_atom(molecule, a2);
  molappend_atom(molecule, a3);
}

void testBondSet(molecule *molecule, bond *bond1, bond *bond2)
{
  /* set the bonds to the atoms stored in the molecule */
  bondset(bond1, &(molecule->atoms[0]), &(molecule->atoms[1]), 1);
  bondset(bond2, &(molecule->atoms[0]), &(molecule->atoms[2]), 1);
}

void testMolappend_bond(molecule *molecule, bond *bond1, bond *bond2)
{
  /* add the bonds */
  molappend_bond(molecule, bond1);
  molappend_bond(molecule, bond2);
}

void testCopy(molecule *molecule)
{
  printf("\nCopied molecule\n");
  // Copy Molecule
  struct molecule *mol2 = molcopy(molecule);
  display_mol(mol2); // Conditional jump or move depends on uninitialised value(s)
  // trying to print values in the bonds (line 49) but only when copying
  molfree(mol2);
}

void testXRotation(molecule *molx, xform_matrix matrix)
{
  printf("\nMolecule for x rotation\n");
  // molx = molcopy(molecule);
  //  display_matrix(matrix);
  xrotation(matrix, 70);
  display_matrix(matrix);
  mol_xform(molx, matrix);
  printf("\n");
  display_mol(molx);
}

void testYRotation(molecule *moly, xform_matrix matrix)
{
  printf("\nSecond molecule, y rotation\n");
  // moly = molcopy(molecule);
  display_matrix(matrix);
  yrotation(matrix, 70);
  display_matrix(matrix);
  mol_xform(moly, matrix);
  printf("\n");
  display_mol(moly);
}

void testZRotation(molecule *molz, xform_matrix matrix)
{
  printf("\nSecond molecule, z rotation\n");
  // molz = molcopy(molecule);
  display_matrix(matrix);
  zrotation(matrix, 70);
  display_matrix(matrix);
  mol_xform(molz, matrix);
  printf("\n");
  display_mol(molz);
}

void testRotations(molecule *molecule)
{
  /* Rotations */
  printf("\nbegin rotations and matrix transformations\n");
  xform_matrix matrix;

  testXRotation(molecule, matrix);
  testYRotation(molecule, matrix);
  testZRotation(molecule, matrix);
}

void testSort(molecule *molecule)
{
  /* Sorting */
  printf("\nSorting the original\n");
  molsort(molecule);
  display_mol(molecule);
  // segfault occurs

  /*struct molecule * mol2 = molcopy(molecule);
  printf("\nSorting the copy\n");
  molsort(mol2);
  printf("Sort done.\n");
  display_mol(mol2);*/
}

int main(int argc, char **argv)
/*
 * create a water molecule and display it
 */
{

  printf("First atom\n");
  // double x, y, z;
  atom a1, a2, a3;
  bond bond1, bond2;
  molecule *molecule;

  testAtomSet(&a1, &a2, &a3);

  /* create the molecule */
  // molecule = molmalloc( 3, 2 );
  // molecule = molmalloc(2, 0);
  molecule = molmalloc(0, 2);

  testMolappend_atom(molecule, &a1, &a2, &a3);

  testBondSet(molecule, &bond1, &bond2);
  testMolappend_bond(molecule, &bond1, &bond2);

  display_mol(molecule);

  testCopy(molecule);

  testRotations(molecule);

  testSort(molecule);

  molfree(molecule);

  return 0;
}
