#include "../includes/dico.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../includes/utils/strutil.h"

#include "../includes/lecture.h"

#include "../includes/memoire.h"

// 

struct sDictionnaire {
    char * Mot;
    int Debut;
    struct sDictionnaire * Suivant;
};

// 

Dictionnaire CreerDico() {
    Dictionnaire dict = Allouer( sizeof(struct sDictionnaire) * 1 );

    dict->Mot = Allouer( sizeof(char) * (TAILLE_MOT_MAX+1) );
    dict->Mot[0] = '\0';
    dict->Debut = -1;
    dict->Suivant = NULL;

    return dict;
}

//

int AjouterDico(char* Mot, Dictionnaire* pDict, int Deb) {
    bool dict_found = false;

    Dictionnaire current_dict = *pDict;

    while(current_dict != NULL && !dict_found) {
        dict_found = strEquals(Mot, current_dict->Mot);

        if(!dict_found)
            current_dict = current_dict->Suivant;
    }

    if(dict_found) {
        current_dict->Debut = Deb;
        return 0;
    }

    // 

    char c = '\1';
    for(int i = 0; c != '\0' && i < TAILLE_MOT_MAX+1; ++i) {
        c = Mot[i];
        (*pDict)->Mot[i] = c;
    }

    (*pDict)->Debut = Deb;

    Dictionnaire new_dict = CreerDico();

    new_dict->Suivant = *pDict;

    *pDict = new_dict;

    return 1;
}

// 

void AfficherDico(Dictionnaire Dict) {
    Dictionnaire current_dict = Dict;

    while(current_dict != NULL) {
        if(current_dict->Debut > 0)
            printf("%s ", current_dict->Mot);

        current_dict = current_dict->Suivant;
    }

    printf("\n");
}

// 

int RechercherDico(char* Mot, Dictionnaire Dict) {
    int result = -1;

    Dictionnaire current_dict = Dict;

    while(current_dict != NULL && result < 0) {
        if(strEquals(Mot, current_dict->Mot))
            result = current_dict->Debut;

        current_dict = current_dict->Suivant;
    }

    return result;
}

// 

void LibererDico(Dictionnaire Dict) {
    Dictionnaire current_dict = Dict;
    Dictionnaire tmp_current_dict;

    while(current_dict != NULL) {
        tmp_current_dict = current_dict;
        current_dict = current_dict->Suivant;
        Liberer(tmp_current_dict->Mot);
        Liberer(tmp_current_dict);
    }
}

// 