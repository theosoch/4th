#include "../../../includes/interpreter/evaluation/operations.h"

// 

#include <stdio.h>

// 

#include "../../../includes/utils/logger.h"
#include "../../../includes/utils/color.h"

#include "../../../includes/utils/strutil.h"
#include "../../../includes/utils/fileutil.h"
#include "../../../includes/utils/pathutil.h"

#include "../../../includes/lecture.h"
#include "../../../includes/pile.h"
#include "../../../includes/dico.h"

#include "../../../includes/interpreter/evaluation/evaluate.h"

#include "../../../includes/interpreter/locale.h"

#include "../../../includes/memoire.h"

// 

bool validProgram(Programme prog, char** eval_words, int eval_word_count) {
    bool valid = true;

    int prog_size = LongueurProg(prog);

    char* word;
    char* next_word;
    bool is_int;

    bool skip_word = false;

    for(int i = 0; i < prog_size && valid; ++i) {
        word = MotProg(prog, i);
        
        str2int(word, &is_int);

        if(!is_int) {
            if(eval_word_count >= MEDIUM_LANGUAGE_WORD_COUNT) {
                // word == "char"
                if(strEquals(word, eval_words[27])) {
                    next_word = MotProg(prog, i+1);
                    if(next_word[0] == '\0' || next_word[1] != '\0') {
                        fprintf(stderr, logger->error("Argument error : `char` keyword must only use a character as argument (not a word by example)."));
                        valid = false;
                    }

                    skip_word = true;
                    i++;
                }
            }
            
            if(skip_word)
                skip_word = false;
            else if(valid && eval_word_count < NORMAL_LANGUAGE_WORD_COUNT) {
                if(!strArrayIncludes((char**) eval_words, 0, eval_word_count, word)) {
                    fprintf(stderr, logger->error("The word `%s` isn't included in the used evaluation words."), word);
                    valid = false;
                }
            }
        }
    }

    return valid;
}

// 

// 

void EvalEmpiler(Pile eval_context_stack, int Elt, int* p_eval_status) {
    if(PilePleine(eval_context_stack)) {
        fprintf(stderr, logger->error("Attempt to stack on a full filled evaluation context stack."));
        *p_eval_status = EVALUATION_ERROR_FULL_STACK_STACKING;
        return;
    }

    Empiler(eval_context_stack, Elt);
}

// 

// 

int EvalDepiler(Pile eval_context_stack, int* p_eval_status) {
    if(PileVide(eval_context_stack)) {
        fprintf(stderr, logger->error("Attempt to unstack on an empty evaluation context stack."));
        *p_eval_status = EVALUATION_ERROR_EMPTY_STACK_UNSTACKING;
        return 0;
    }

    return Depiler(eval_context_stack);
}

// 

// 

void EVAL_DOT_S(Pile eval_context_stack) {
    AfficherPile(eval_context_stack);
}

// 

// 

void EVAL_DOT(Pile eval_context_stack, int* p_eval_status) {
    int top = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    printf("%d\n", top);
}

// 

// 

void EVAL_DUP(Pile eval_context_stack, int* p_eval_status) {
    EvalEmpiler(eval_context_stack, SommetPile(eval_context_stack), p_eval_status);
}

// 

// 

void EVAL_DROP(Pile eval_context_stack, int* p_eval_status) {
    EvalDepiler(eval_context_stack, p_eval_status);
}

// 

// 

void EVAL_SWAP(Pile eval_context_stack, int* p_eval_status) {
    int swap_tab[2] = { 0, 0 };

    swap_tab[0] = EvalDepiler(eval_context_stack, p_eval_status);
    swap_tab[1] = EvalDepiler(eval_context_stack, p_eval_status);
    
    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    EvalEmpiler(eval_context_stack, swap_tab[0], p_eval_status);
    EvalEmpiler(eval_context_stack, swap_tab[1], p_eval_status);
}

// 

// 

void EVAL_OVER(Pile eval_context_stack, int* p_eval_status) {
    int over_storage[2] = { 0, 0 };
    over_storage[0] = EvalDepiler(eval_context_stack, p_eval_status);
    over_storage[1] = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    EvalEmpiler(eval_context_stack, over_storage[1], p_eval_status);
    EvalEmpiler(eval_context_stack, over_storage[0], p_eval_status);
    EvalEmpiler(eval_context_stack, over_storage[1], p_eval_status);
}

// 

// ARITHMETICAL OPERATIONS

#define ARITHMETICAL_OPERATION_ADD 0
#define ARITHMETICAL_OPERATION_SUBSTRACT 1
#define ARITHMETICAL_OPERATION_MULTIPLY 2
#define ARITHMETICAL_OPERATION_DIVIDE 3
#define ARITHMETICAL_OPERATION_MODULO 4

void EVAL_ARITHMETICAL_OPERATION(Pile eval_context_stack, int operation, int* p_eval_status) {
    int operation_storage_tab[2] = { 0, 0 };

    operation_storage_tab[1] = EvalDepiler(eval_context_stack, p_eval_status);
    operation_storage_tab[0] = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    if(operation == ARITHMETICAL_OPERATION_ADD)
        operation_storage_tab[0] = operation_storage_tab[0] + operation_storage_tab[1];
    else if(operation == ARITHMETICAL_OPERATION_SUBSTRACT)
        operation_storage_tab[0] = operation_storage_tab[0] - operation_storage_tab[1];
    else if(operation == ARITHMETICAL_OPERATION_MULTIPLY)
        operation_storage_tab[0] = operation_storage_tab[0] * operation_storage_tab[1];
    else if(operation == ARITHMETICAL_OPERATION_DIVIDE) {
        if(operation_storage_tab[1] == 0) {
            *p_eval_status = EVALUATION_ERROR_DIVISION_BY_ZERO;
            return;
        }

        operation_storage_tab[0] = operation_storage_tab[0] / operation_storage_tab[1];
    }
    else if(operation == ARITHMETICAL_OPERATION_MODULO) {
        if(operation_storage_tab[1] == 0) {
            *p_eval_status = EVALUATION_ERROR_DIVISION_BY_ZERO;
            return;
        }

        operation_storage_tab[0] = operation_storage_tab[0] % operation_storage_tab[1];
    }

    EvalEmpiler(eval_context_stack, operation_storage_tab[0], p_eval_status);
}

// 

// LOGICAL OPERATIONS

#define LOGICAL_OPERATION_EQUAL 0
#define LOGICAL_OPERATION_LESSER 1
#define LOGICAL_OPERATION_LESSER_OR_EQUAL 2
#define LOGICAL_OPERATION_GREATER 3
#define LOGICAL_OPERATION_GREATER_OR_EQUAL 4
#define LOGICAL_OPERATION_AND 5
#define LOGICAL_OPERATION_OR 6
#define LOGICAL_OPERATION_NOT 7

void EVAL_LOGICAL_OPERATION(Pile eval_context_stack, int operation, int* p_eval_status) {
    int operation_storage_tab[2] = { 0, 0 };

    operation_storage_tab[1] = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    if(operation >= LOGICAL_OPERATION_EQUAL && operation <= LOGICAL_OPERATION_OR) {
        operation_storage_tab[0] = EvalDepiler(eval_context_stack, p_eval_status);
        if(operation == LOGICAL_OPERATION_EQUAL)
            operation_storage_tab[0] = operation_storage_tab[0] == operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_LESSER)
            operation_storage_tab[0] = operation_storage_tab[0] < operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_LESSER_OR_EQUAL)
            operation_storage_tab[0] = operation_storage_tab[0] <= operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_GREATER)
            operation_storage_tab[0] = operation_storage_tab[0] > operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_GREATER_OR_EQUAL)
            operation_storage_tab[0] = operation_storage_tab[0] >= operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_AND)
            operation_storage_tab[0] = operation_storage_tab[0] && operation_storage_tab[1];
        else if(operation == LOGICAL_OPERATION_OR)
            operation_storage_tab[0] = operation_storage_tab[0] || operation_storage_tab[1];

        EvalEmpiler(eval_context_stack, operation_storage_tab[0], p_eval_status);
    }
    else if(operation == LOGICAL_OPERATION_NOT) {
        operation_storage_tab[1] = operation_storage_tab[1] == 0;
        EvalEmpiler(eval_context_stack, operation_storage_tab[1], p_eval_status);
    }
}

// 

// 

void EVAL_LOGICAL_CONTROL_IF(Pile eval_context_stack, const char** eval_words, Programme prog, int excluded_word_end, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status) {
    int else_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_index, (char*) eval_words[19], (char*) eval_words[20], 1);
    int endif_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_index, (char*) eval_words[19], (char*) eval_words[21], 1);

    // if(else_index < 0) {
    //     *p_eval_status = EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ELSE;
    //     return;
    // }
    if(endif_index < 0) {
        *p_eval_status = EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_ENDIF;
        return;
    }

    // 

    int top = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    // printf("--| %d ; %d ; %d\n", top, else_index, endif_index);


    EvalEmpiler(WORD_I_JUMP_STACK, endif_index+1, p_eval_status); // Stacking WORD_I_JUMP_TO
    EvalEmpiler(WORD_I_JUMP_STACK, endif_index, p_eval_status); // Stacking WORD_I_JUMP_FROM

    if(top) {
        if(else_index > 0) {
            EvalEmpiler(WORD_I_JUMP_STACK, endif_index+1, p_eval_status); // Stacking WORD_I_JUMP_TO
            EvalEmpiler(WORD_I_JUMP_STACK, else_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
        }
    }
    else {
        EvalEmpiler(WORD_I_JUMP_STACK, (else_index > 0 ? else_index : endif_index)+1, p_eval_status); // Stacking WORD_I_JUMP_TO
        EvalEmpiler(WORD_I_JUMP_STACK, word_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
    }
}

// 

// 

void EVAL_LOOP_CONTROL_WHILE(Pile eval_context_stack, const char** eval_words, Programme prog, int excluded_word_end, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status) {
    int begin_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_index, (char*) eval_words[23], (char*) eval_words[22], -1);
    int repeat_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_index, (char*) eval_words[23], (char*) eval_words[24], 1);

    if(begin_index < 0) {
        *p_eval_status = EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_BEGIN;
        return;
    }
    else if(repeat_index < 0) {
        *p_eval_status = EVALUATION_ERROR_INVALID_LOOP_SYNTAX_MISSING_KEYWORD_REPEAT;
        return;
    }

    // 

    int top = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    if(top) {
        EvalEmpiler(WORD_I_JUMP_STACK, begin_index, p_eval_status); // Stacking WORD_I_JUMP_TO
        EvalEmpiler(WORD_I_JUMP_STACK, repeat_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
    }
    else {
        EvalEmpiler(WORD_I_JUMP_STACK, repeat_index+1, p_eval_status); // Stacking WORD_I_JUMP_TO
        EvalEmpiler(WORD_I_JUMP_STACK, word_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
    }
}

// 

// 

void EVAL_EMIT(Pile eval_context_stack, int* p_eval_status) {
    int charcode = EvalDepiler(eval_context_stack, p_eval_status);
    
    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    printf("%c", (char) charcode);
}

// 

// 

void EVAL_KEY(Pile eval_context_stack, int* p_eval_status) {
    char keychar;
    scanf("%c", &keychar);
    EvalEmpiler(eval_context_stack, (int) keychar, p_eval_status);
}

// 

// 

void EVAL_CHAR(Pile eval_context_stack, Programme prog, int excluded_word_end, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status) {
    if(word_index+1 >= excluded_word_end) {
        *p_eval_status = EVALUATION_ERROR_PROGRAM_END_REACHED;
        return;
    }

    char* next_word = MotProg(prog, word_index+1);

    if(next_word[0] == '\0' || next_word[1] != '\0') {
        *p_eval_status = EVALUATION_ERROR_INVALID_CHAR_OPERATOR_SYNTAX_WORD_OR_NON_CHAR_USED_AS_OPERATOR_ARGUMENT;
    }

    EvalEmpiler(eval_context_stack, (int) next_word[0], p_eval_status);

    EvalEmpiler(WORD_I_JUMP_STACK, word_index+2, p_eval_status); // Stacking WORD_I_JUMP_TO
    EvalEmpiler(WORD_I_JUMP_STACK, word_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
}

// 

// 

void EVAL_CR() {
    printf("\n");
}

// 

// 

void EVAL_SPACE() {
    printf(" ");
}

// 

// 

void EVAL_SPACES(Pile eval_context_stack, int* p_eval_status) {
    int space_count = EvalDepiler(eval_context_stack, p_eval_status);

    if(*p_eval_status != EVALUATION_SUCCESS)
        return;

    for(int i = 0; i < space_count; ++i)
        EVAL_SPACE();
}

// 

// 

void EVAL_DOT_QUOTE(Programme prog, int excluded_word_end, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status) {
    if(word_index+1 >= excluded_word_end) {
        *p_eval_status = EVALUATION_ERROR_PROGRAM_END_REACHED;
        return;
    }

    EvalEmpiler(WORD_I_JUMP_STACK, word_index+2, p_eval_status); // Stacking WORD_I_JUMP_TO
    EvalEmpiler(WORD_I_JUMP_STACK, word_index+1, p_eval_status); // Stacking WORD_I_JUMP_FROM

    printf(color(MotProg(prog, word_index+1)));
}

// 

// 

void EVAL_INTEGER_INPUT(Pile eval_context_stack, int* p_eval_status) {
    int n_in;
    char c;
    scanf("%d", &n_in);
    scanf("%c", &c);
    EvalEmpiler(eval_context_stack, n_in, p_eval_status);
}

// 

// 

void EVAL_WORD_DEFINITION(Programme prog, int excluded_word_end, const char** eval_words, int eval_word_count, int word_index, Pile WORD_I_JUMP_STACK, Dictionnaire* p_eval_context_dict, int* p_eval_status) {
    if(word_index+2 >= excluded_word_end) {
        *p_eval_status = EVALUATION_ERROR_PROGRAM_END_REACHED;
        return;
    }

    char* def_word = MotProg(prog, word_index+1);

    if(strArrayIncludes((char**) eval_words, 0, eval_word_count, def_word)) {
        *p_eval_status = EVALUATION_ERROR_WORD_ALREADY_IN_LANGUAGE_WORDS;
        return;
    }

    int def_end_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_index, (char*) eval_words[33], (char*) eval_words[34], 1);

    if(def_end_index < 0) {
        *p_eval_status = EVALUATION_ERROR_INVALID_WORD_DEFINITION_SYNTAX_MISSING_DEF_CLOSING_WORD;
        return;
    }

    AjouterDico(def_word, p_eval_context_dict, word_index+2);

    EvalEmpiler(WORD_I_JUMP_STACK, def_end_index, p_eval_status); // Stacking WORD_I_JUMP_TO
    EvalEmpiler(WORD_I_JUMP_STACK, word_index, p_eval_status); // Stacking WORD_I_JUMP_FROM
}

// 

// 

void EVAL_WORDS_KEYWORD(Dictionnaire* p_eval_context_dict) {
    AfficherDico(*p_eval_context_dict);
}

// 

//

void EVAL_INCLUDE(Programme prog, char* dirname, int excluded_word_end, const char** eval_words, int eval_word_count, int word_index, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int* p_eval_status) {
    char* included_prog_filepath = MotProg(prog, word_index)+strLength((char*) eval_words[36])+1;

    if(!fexists(included_prog_filepath)) {
        char* x = pathJoin(dirname, included_prog_filepath);
        included_prog_filepath = pathResolve(x);
    }

    if(!fexists(included_prog_filepath)) {
        fprintf(stderr, logger->error("Included file `%s` not found."), included_prog_filepath);
        *p_eval_status = CLI_ERROR_PROGRAM_FILE_NOT_FOUND;
        return;
    }

    // 

    // Programme included_prog = LectureProg(included_prog_filepath);

    // int inclusion_status = AppendProg(prog, included_prog);

    // if(inclusion_status <= 0) {
    //     fprintf(stderr, logger->error("Include `%s` failed."), included_prog_filepath);
    //     return;
    // }

    // LibererProg(included_prog);

    // 

    Programme inclusion_result = ReadAppendProg(included_prog_filepath, prog);

    if(inclusion_result == NULL) {
        fprintf(stderr, logger->error("Include `%s` failed."), included_prog_filepath);
        *p_eval_status = EVALUATION_ERROR_INCLUDE_FAILED;
        return;
    }

    // 

    *p_eval_status = evaluate(prog, pathDirname(included_prog_filepath), excluded_word_end, LongueurProg(prog), eval_word_count, eval_context_stack, p_eval_context_dict, -1);
}

//
