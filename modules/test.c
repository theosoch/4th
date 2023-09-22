#include "../includes/test.h"

// 

#include <stdio.h>

// 

#include "../includes/utils/tempalloc.h"

#include "../includes/utils/logger.h"

#include "../includes/lecture.h"
#include "../includes/pile.h"

#include "../includes/memoire.h"

// 

void test() {
    Programme progtest = LectureProg("./resources/tests/progtest.forth");

    if(progtest != NULL) {
        // fprintf(stdout, logger->info("Program resolved."));
        fprintf(stdout, "Program resolved.\n");

        //

        printf("%d\n", LongueurProg(progtest));

        Bilan();

        AfficherProg(progtest);

        Bilan();

        LibererProg(progtest);

        Bilan();
    }
    else
        // fprintf(stderr, logger->error("Program not resolved !"));
        fprintf(stderr, "Program not resolved !\n");

    // 

    Pile p = CreerPile();

    if(p != NULL) {
        // fprintf(stdout, logger->info("Pile successfully initialized."));
        fprintf(stdout, "Pile successfully initialized.\n");

        //

        AfficherPile(p);
        // AfficherPileDebug(p);

        Empiler(p, 2);
        Empiler(p, 3);
        Empiler(p, 7);

        // AfficherPileDebug(p);
        AfficherPile(p);

        printf("%d\n", Depiler(p));

        // AfficherPileDebug(p);
        AfficherPile(p);

        LibererPile(p);

        Bilan();
    }
    else
        // fprintf(stderr, logger->error("Pile not initialized !"));
        fprintf(stderr, "Pile not initialized !\n");

    tempalloc->freeall();

    Bilan();

    // 

    return;
}