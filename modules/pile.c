#include "../includes/pile.h"

// 

#include <stdio.h>
#include "../includes/memoire.h"

// 

struct sCellule {
    int Valeur;
    struct sCellule * Suivant;
};

typedef struct sCellule * Cellule;

// 

struct sPile {
    unsigned int Hauteur;
    bool Vide;
    bool Pleine;
    struct sCellule * Sommet;
};

// 

Pile CreerPile() {
    Pile p = Allouer( sizeof(struct sPile) * 1 );

    if(p != NULL) {
        p->Hauteur = 0;
        p->Vide = true;
        p->Pleine = false;
        p->Sommet = NULL;
    }

    return p;
}

// 

bool PileVide(Pile p) {
    return p->Vide;
}

// 

bool PilePleine(Pile p) {
    return p->Pleine;
}

// 

unsigned int HauteurPile(Pile p) {
    return p->Hauteur;
}

// 

void Empiler(Pile p, int Elt) {
    if(PilePleine(p))
        return;

    // 

    Cellule new_cell = Allouer( sizeof(struct sCellule) * 1 );

    new_cell->Valeur = Elt;
    new_cell->Suivant = p->Sommet;

    p->Sommet = new_cell;

    p->Hauteur = HauteurPile(p) + 1;

    if(PileVide(p))
        p->Vide = false;

    if(HauteurPile(p) == PILE_HAUTEUR_MAX)
        p->Pleine = true;
}

// 

int SommetPile(Pile p) {
    return PileVide(p) ? 0 : p->Sommet->Valeur;
}

// 

int Depiler(Pile p) {
    if(PileVide(p))
        return 0;

    // 

    int result;
    Cellule top = p->Sommet;

    result = top->Valeur;
    p->Sommet = top->Suivant;

    Liberer(top);

    p->Hauteur = HauteurPile(p) - 1;

    if(HauteurPile(p) == 0)
        p->Vide = true;

    if(PilePleine(p))
        p->Pleine = false;

    return result;
}

// 

void AfficherPile(Pile p) {
    printf("<%d>", HauteurPile(p));

    Pile tmp_stack = CreerPile();

    Cellule pile_cell = p->Sommet;

    while(pile_cell != NULL) {
        Empiler(tmp_stack, pile_cell->Valeur);
        pile_cell = pile_cell->Suivant;
    }
    
    while(HauteurPile(tmp_stack) > 0)
        printf(" %d", Depiler(tmp_stack));

    LibererPile(tmp_stack);

    printf("\n");

    // if(HauteurPile(p) > 0) {
    //     if(HauteurPile(p) < 2) {
    //         printf("%d", SommetPile(p));
    //     }
    //     else {
    //         printf("<%d>", HauteurPile(p));

    //         Pile tmp_stack = CreerPile();

    //         Cellule pile_cell = p->Sommet;

    //         while(pile_cell != NULL) {
    //             Empiler(tmp_stack, pile_cell->Valeur);
    //             pile_cell = pile_cell->Suivant;
    //         }
            
    //         while(HauteurPile(tmp_stack) > 0)
    //             printf(" %d", Depiler(tmp_stack));

    //         LibererPile(tmp_stack);
    //     }
    // }
    // printf("\n");
}

// 

void AfficherPileDebug(Pile p) {
    fprintf(stdout, logger->debug("(<%d>\1"), HauteurPile(p));

    Pile tmp_stack = CreerPile();

    Cellule pile_cell = p->Sommet;

    while(pile_cell != NULL) {
        Empiler(tmp_stack, pile_cell->Valeur);
        pile_cell = pile_cell->Suivant;
    }
    
    while(HauteurPile(tmp_stack) > 0)
        printf(" %d", Depiler(tmp_stack));

    LibererPile(tmp_stack);

    if(HauteurPile(p) == 0)
        printf(" ");

    fprintf(stdout, ")\n");
}

// 

void LibererPile(Pile p) {
    Cellule pile_cell = p->Sommet;
    Cellule pile_cell_temp;

    while(pile_cell != NULL) {
        pile_cell_temp = pile_cell;
        pile_cell = pile_cell->Suivant;
        Liberer(pile_cell_temp);
    }

    Liberer(p);
}

// 