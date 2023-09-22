#include <stdio.h>
#include <stdbool.h>

// 

#include "../includes/utils/tempalloc.h"

#include "../includes/test.h"

#include "../includes/interpreter/cli.h"
#include "../includes/interpreter/locale.h"

#include "../includes/pile.h"
#include "../includes/dico.h"

#include "../includes/memoire.h"

// 

#define REVIEW_VERSION 0

static int EXIT_STATUS;

// 

int main(int argc, char** argv) {
    // test();

    // 

    Pile eval_context_stack = CreerPile();
    Dictionnaire eval_context_dict = CreerDico();

    int debuglevel;

    EXIT_STATUS = cli(argc, argv, eval_context_stack, &eval_context_dict, &debuglevel);

    LibererPile(eval_context_stack);
    LibererDico(eval_context_dict);

    tempalloc->freeall();

    if(REVIEW_VERSION || debuglevel > 0)
        Bilan();

    // 

    return EXIT_STATUS;
}