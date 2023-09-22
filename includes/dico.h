#pragma once

// 

#ifndef __DICO_H__
#define __DICO_H__

// 

typedef struct sDictionnaire * Dictionnaire;

// 

extern Dictionnaire CreerDico();

// 

extern int AjouterDico(char* Mot, Dictionnaire* pDict, int Deb);

// 

extern void AfficherDico(Dictionnaire Dict);

// 

extern int RechercherDico(char* Mot, Dictionnaire Dict);

// 

extern void LibererDico(Dictionnaire Dict);

// 

#endif