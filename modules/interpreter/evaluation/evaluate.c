#include "../../../includes/interpreter/evaluation/evaluate.h"

// 

#include <stdio.h>

// 

#include "../../../includes/interpreter/evaluation/level1.h"
#include "../../../includes/interpreter/evaluation/level2.h"
#include "../../../includes/interpreter/evaluation/level3.h"
#include "../../../includes/interpreter/evaluation/level4.h"

#include "../../../includes/interpreter/evaluation/operations.h"

#include "../../../includes/interpreter/locale.h"

// 

int evaluate(Programme prog, char* dirname, int included_word_start, int excluded_word_end, int eval_word_count, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int debuglevel) {
    int eval_status = EVALUATION_SUCCESS;

    // 

    if(validProgram(prog, (char**) LANGUAGE_WORDS, eval_word_count)) {
        if(debuglevel > 0)
                fprintf(stdout, logger->debug("Used program is valid."));
    }
    else {
        fprintf(stderr, logger->error("This program is not a valid program for this interpreter level."));
        eval_status = EVALUATION_ERROR_INVALID_PROGRAM;
        return eval_status;
    }

    // 

    if(debuglevel > 0) {
        fprintf(stdout, logger->debug("Used evaluation context stack (before evaluation) :"));
        AfficherPileDebug(eval_context_stack);
        
        fprintf(stdout, logger->debug("Evaluation logs :"));
    }

    // 

    if(eval_word_count <= BASIC_LANGUAGE_WORD_COUNT)
        eval_status = EVALUATE_LEVEL_1(prog, included_word_start, excluded_word_end, eval_context_stack);
    else if(eval_word_count <= MEDIUM_LANGUAGE_WORD_COUNT)
        eval_status = EVALUATE_LEVEL_2(prog, included_word_start, excluded_word_end, eval_context_stack);
    else if(eval_word_count <= NORMAL_LANGUAGE_WORD_COUNT)
        eval_status = EVALUATE_LEVEL_3(prog, included_word_start, excluded_word_end, eval_context_stack, p_eval_context_dict);
    else if(eval_word_count <= ADVANCED_LANGUAGE_WORD_COUNT)
        eval_status = EVALUATE_LEVEL_4(prog, dirname, included_word_start, excluded_word_end, eval_context_stack, p_eval_context_dict);

    // 

    if(debuglevel > 0) {
        fprintf(stdout, logger->debug("Used evaluation context stack (after evaluation) :"));
        AfficherPileDebug(eval_context_stack);
    }

    // 

    if(debuglevel >= 0) {
        if(eval_status == EVALUATION_SUCCESS && debuglevel > 0)
            fprintf(stderr, logger->debug("&aSuccess !"));

        else if(eval_status == EVALUATION_ERROR_NOT_SUPPORTED_WORD)
            fprintf(stderr, logger->error("EVALUATION_ERROR_NOT_SUPPORTED_WORD"));
        else if(eval_status == EVALUATION_ERROR_PROGRAM_END_REACHED)
            fprintf(stderr, logger->error("EVALUATION_ERROR_PROGRAM_END_REACHED"));
        
        else if(eval_status == EVALUATION_ERROR_EMPTY_STACK_UNSTACKING)
            fprintf(stderr, logger->error("EVALUATION_ERROR_EMPTY_STACK_UNSTACKING"));
        else if(eval_status == EVALUATION_ERROR_FULL_STACK_STACKING)
            fprintf(stderr, logger->error("EVALUATION_ERROR_FULL_STACK_STACKING"));

        else if(eval_status == EVALUATION_ERROR_DIVISION_BY_ZERO)
            fprintf(stderr, logger->error("EVALUATION_ERROR_DIVISION_BY_ZERO"));
        
        else if(eval_status == EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_IF)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_IF"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ELSE)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ELSE"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ENDIF)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ENDIF"));
        
        else if(eval_status == EVALUATION_ERROR_INVALID_LOOP_SYNTAX)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOOP_SYNTAX"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_BEGIN)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_BEGIN"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_WHILE)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_WHILE"));
        else if(eval_status == EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_REPEAT)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_REPEAT"));

        else if(eval_status == EVALUATION_ERROR_INVALID_CHAR_OPERATOR_SYNTAX_WORD_OR_NON_CHAR_USED_AS_OPERATOR_ARGUMENT)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_CHAR_OPERATOR_SYNTAX_WORD_OR_NON_CHAR_USED_AS_OPERATOR_ARGUMENT"));
        
        else if(eval_status == EVALUATION_ERROR_INVALID_DOT_QUOTE_SYNTAX)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_DOT_QUOTE_SYNTAX"));
        
        else if(eval_status == EVALUATION_ERROR_INVALID_INTEGER_INPUT_VALUE)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_INTEGER_INPUT_VALUE"));

        else if(eval_status == EVALUATION_ERROR_WORD_ALREADY_IN_LANGUAGE_WORDS)
            fprintf(stderr, logger->error("EVALUATION_ERROR_WORD_ALREADY_IN_LANGUAGE_WORDS"));
        else if(eval_status == EVALUATION_ERROR_INVALID_WORD_DEFINITION_SYNTAX_MISSING_DEF_CLOSING_WORD)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_WORD_DEFINITION_SYNTAX_MISSING_DEF_CLOSING_WORD"));

        else if(eval_status == EVALUATION_ERROR_INCLUDE_FAILED)
            fprintf(stderr, logger->error("EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_REPEAT"));
    }

    // 

    return eval_status;
}

// 