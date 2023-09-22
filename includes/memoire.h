/* 25/10/2022 A. Crouzil  memoire version 1.1 */
/* NE PAS MODIFIER CE FICHIER */
#ifndef MEMOIRE_H
#define MEMOIRE_H
#include <stddef.h>

/*
 * Remplace malloc
 */
extern void *Allouer(size_t NbOctets);

/*
 * Remplace free
 */
extern void Liberer(void *Adresse);

/*
 * Affiche le bilan de la gestion dynamique de la mémoire
 */
extern void Bilan(void);


/*
 * Définir la constante symbolique SANS_VERIF avant l'inclusion de ce fichier
 * pour ne pas effectuer de vérification de la gestion dynamique de la mémoire
 */

#ifndef SANS_VERIF
  #define malloc Allouer
  #define free Liberer
#else
  #include <stdlib.h>
  #define Allouer malloc
  #define Liberer free
  #define Bilan()
#endif


#endif /* MEMOIRE_H */
