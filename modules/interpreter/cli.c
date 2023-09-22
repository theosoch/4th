#include "../../includes/interpreter/cli.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../../includes/utils/logger.h"

#include "../../includes/utils/strutil.h"
#include "../../includes/utils/pathutil.h"
#include "../../includes/utils/fileutil.h"

#include "../../includes/lecture.h"
#include "../../includes/pile.h"
#include "../../includes/dico.h"

#include "../../includes/interpreter/evaluation/operations.h"
#include "../../includes/interpreter/evaluation/evaluate.h"

#include "../../includes/interpreter/locale.h"

// 

int cli(int argc, char** argv, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int* p_debuglevel) {
    int eval_status = EVALUATION_SUCCESS;

    // 

    *p_debuglevel = 0;
    bool debug_arg_found = false;

    for(int i = 1; i < argc && !debug_arg_found; ++i) {
        if(strEquals(argv[i], "--debug") && i < argc) {
            *p_debuglevel = 1;
            debug_arg_found = true;
        }
    }

    // 

    char* prog_filepath = NULL;

    for(int i = 1; i < argc && prog_filepath == NULL; ++i) {
        if(!strStartsWith(argv[i], "-")) {
            prog_filepath = argv[i];
        }
    }

    // 

    if(prog_filepath == NULL) {
        fprintf(stderr, logger->error("Program file path not specified."));
        return CLI_ERROR_PROGRAM_FILE_NOT_FOUND;
    }

    // 

    int eval_word_count = ADVANCED_LANGUAGE_WORD_COUNT;

    if(fexists(prog_filepath)) {
        Programme prog = LectureProg(prog_filepath);

        // 

        if(prog != NULL) {
            for(int i = 1; i < argc && eval_word_count < 0; ++i) {
                if(strEquals(argv[i], "--basic"))
                    eval_word_count = BASIC_LANGUAGE_WORD_COUNT;
                else if(strEquals(argv[i], "--medium"))
                    eval_word_count = MEDIUM_LANGUAGE_WORD_COUNT;
                else if(strEquals(argv[i], "--normal"))
                    eval_word_count = NORMAL_LANGUAGE_WORD_COUNT;
                else if(strEquals(argv[i], "--advanced"))
                    eval_word_count = ADVANCED_LANGUAGE_WORD_COUNT;
            }

            // 

            eval_status = evaluate(prog, pathDirname(prog_filepath), 0, LongueurProg(prog), eval_word_count, eval_context_stack, p_eval_context_dict, *p_debuglevel);

            // 

            LibererProg(prog);
        }
    }
    else
        fprintf(stderr, logger->error("Program file not found."));

    // 

    return eval_status;
}