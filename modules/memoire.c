/* 25/10/2022 A. Crouzil  memoire version 1.1 */
/* NE PAS MODIFIER CE FICHIER */
#include <stdio.h>
#include <stdlib.h>

/* Actions possibles */
typedef enum eAction { allouer, liberer, bilan } Action;

/* Fonction permettant la vérification de la gestion de la mémoire */
static void Compta(Action a)
{
  static int NbAlloc=0, NbFree=0;

  switch (a)
  {
  case allouer: NbAlloc++; break;
  case liberer: NbFree++; break;
  case bilan :
    fprintf(stderr,"\nBilan de la gestion dynamique de la mémoire :\n");
    fprintf(stderr,"\tNombre d'allocations : \t%d\n",NbAlloc);
    fprintf(stderr,"\tNombre de libérations :\t%d\n",NbFree);
    if (NbFree==NbAlloc)
      fprintf(stderr,"Nombre d'allocations = Nombre de libérations.\n");
    else
      fprintf(stderr,"Problème de gestion de la mémoire.\n");
  }
}

/* Remplace malloc */
void *Allouer(size_t NbOctets)
{
  void *Adresse=NULL;

  if (NbOctets && ((Adresse=malloc(NbOctets))!=NULL)) Compta(allouer);
  return Adresse;
}


/* Remplace free */
void Liberer(void *Adresse)
{
  if (Adresse!=NULL)
  {
    free(Adresse);
    Compta(liberer);
  }
}


/* Affiche le bilan de la gestion dynamique de la mémoire */
void Bilan(void)
{
  Compta(bilan);
}
