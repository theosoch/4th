#include "../../../includes/interpreter/evaluation/level3.h"

// 

#include <stdio.h>

// 

#include "../../../includes/utils/logger.h"

#include "../../../includes/utils/strutil.h"
#include "../../../includes/utils/fileutil.h"

#include "../../../includes/lecture.h"
#include "../../../includes/pile.h"
#include "../../../includes/dico.h"

#include "../../../includes/interpreter/evaluation/operations.h"

#include "../../../includes/interpreter/locale.h"

// 

int EVALUATE_LEVEL_3(Programme prog, int included_word_start, int excluded_word_end, Pile eval_context_stack, Dictionnaire* p_eval_context_dict) {
    int eval_word_count = NORMAL_LANGUAGE_WORD_COUNT;

    // 

    const char** eval_words = LANGUAGE_WORDS;

    // 

    int eval_status = EVALUATION_SUCCESS;

    // 

    Pile WORD_I_JUMP_STACK = CreerPile();

    // 

    int word_dict_def_index = -1;

    // 

    char* word;
    bool is_int;
    int n;

    for(int i = included_word_start; i < excluded_word_end && eval_status == EVALUATION_SUCCESS; ++i) {
        if(!PileVide(WORD_I_JUMP_STACK) && i >= SommetPile(WORD_I_JUMP_STACK)) {
            EvalDepiler(WORD_I_JUMP_STACK, &eval_status);
            i = EvalDepiler(WORD_I_JUMP_STACK, &eval_status);
        }

        // 

        if(i < excluded_word_end) {
            word = MotProg(prog, i);

            n = str2int(word, &is_int); 

            if(is_int)
                EvalEmpiler(eval_context_stack, n, &eval_status);
            else if(strArrayIncludes((char**) eval_words, 0, eval_word_count, word)) {
                // word == ".s"
                if(strEquals(word, (char*) eval_words[0]))
                    EVAL_DOT_S(eval_context_stack);
                // word == "."
                else if(strEquals(word, (char*) eval_words[1]))
                    EVAL_DOT(eval_context_stack, &eval_status);
                // word == "dup"
                else if(strEquals(word, (char*) eval_words[2]))
                    EVAL_DUP(eval_context_stack, &eval_status);
                // word == "drop"
                else if(strEquals(word, (char*) eval_words[3]))
                    EVAL_DROP(eval_context_stack, &eval_status);
                // word == "swap"
                else if(strEquals(word, (char*) eval_words[4]))
                    EVAL_SWAP(eval_context_stack, &eval_status);
                // word == "over"
                else if(strEquals(word, (char*) eval_words[5]))
                    EVAL_OVER(eval_context_stack, &eval_status);

                // 

                // word == "+"
                else if(strEquals(word, (char*) eval_words[6]))
                    EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_ADD, &eval_status);
                // word == "-"
                else if(strEquals(word, (char*) eval_words[7]))
                    EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_SUBSTRACT, &eval_status);
                // word == "*"
                else if(strEquals(word, (char*) eval_words[8]))
                    EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_MULTIPLY, &eval_status);
                // word == "/"
                else if(strEquals(word, (char*) eval_words[9]))
                    EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_DIVIDE, &eval_status);
                // word == "%"
                else if(strEquals(word, (char*) eval_words[10]))
                    EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_MODULO, &eval_status);

                //

                // word == "="
                else if(strEquals(word, (char*) eval_words[11]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_EQUAL, &eval_status);
                // word == "<"
                else if(strEquals(word, (char*) eval_words[12]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_LESSER, &eval_status);
                // word == "<="
                else if(strEquals(word, (char*) eval_words[13]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_LESSER_OR_EQUAL, &eval_status);
                // word == ">"
                else if(strEquals(word, (char*) eval_words[14]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_GREATER, &eval_status);
                // word == ">="
                else if(strEquals(word, (char*) eval_words[15]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_GREATER_OR_EQUAL, &eval_status);
                // word == "and"
                else if(strEquals(word, (char*) eval_words[16]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_AND, &eval_status);
                // word == "or"
                else if(strEquals(word, (char*) eval_words[17]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_OR, &eval_status);
                // word == "not"
                else if(strEquals(word, (char*) eval_words[18]))
                    EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_NOT, &eval_status);

                // 

                // word == "if"
                else if(strEquals(word, (char*) eval_words[19]))
                    EVAL_LOGICAL_CONTROL_IF(eval_context_stack, eval_words, prog, excluded_word_end, i, WORD_I_JUMP_STACK, &eval_status);
                else if(
                    strEquals(word, (char*) eval_words[20])
                    || strEquals(word, (char*) eval_words[21])
                ) {
                    eval_status = EVALUATION_ERROR_INVALID_LOGICAL_CONTROL_SYNTAX_MISSING_KEYWORD_IF;
                }

                // 

                // word == "while"
                else if(strEquals(word, (char*) eval_words[23]))
                    EVAL_LOOP_CONTROL_WHILE(eval_context_stack, eval_words, prog, excluded_word_end, i, WORD_I_JUMP_STACK, &eval_status);

                // 

                // word == "emit"
                else if(strEquals(word, (char*) eval_words[25]))
                    EVAL_EMIT(eval_context_stack, &eval_status);
                // word == "key"
                else if(strEquals(word, (char*) eval_words[26]))
                    EVAL_KEY(eval_context_stack, &eval_status);
                // word == "char"
                else if(strEquals(word, (char*) eval_words[27]))
                    EVAL_CHAR(eval_context_stack, prog, excluded_word_end, i, WORD_I_JUMP_STACK, &eval_status);
                // word == "cr"
                else if(strEquals(word, (char*) eval_words[28]))
                    EVAL_CR();
                // word == "space"
                else if(strEquals(word, (char*) eval_words[29]))
                    EVAL_SPACE();
                // word == "spaces"
                else if(strEquals(word, (char*) eval_words[30]))
                    EVAL_SPACES(eval_context_stack, &eval_status);
                // word == ".\""
                else if(strEquals(word, (char*) eval_words[31]))
                    EVAL_DOT_QUOTE(prog, excluded_word_end, i, WORD_I_JUMP_STACK, &eval_status);
                // word == "#in"
                else if(strEquals(word, (char*) eval_words[32]))
                    EVAL_INTEGER_INPUT(eval_context_stack, &eval_status);
                    
                // word == ":"
                else if(strEquals(word, (char*) eval_words[33]))
                    EVAL_WORD_DEFINITION(prog, excluded_word_end, eval_words, eval_word_count, i, WORD_I_JUMP_STACK, p_eval_context_dict, &eval_status);
                // word == "words"
                else if(strEquals(word, (char*) eval_words[35]))
                    EVAL_WORDS_KEYWORD(p_eval_context_dict);
            }
            else if((word_dict_def_index = RechercherDico(word, *p_eval_context_dict)) > 0) {
                int def_end_index = searchClosingWord(ProgWordArray(prog), excluded_word_end, word_dict_def_index-2, (char*) eval_words[33], (char*) eval_words[34], 1);

                EvalEmpiler(WORD_I_JUMP_STACK, i+1, &eval_status); // Stacking WORD_I_JUMP_TO
                EvalEmpiler(WORD_I_JUMP_STACK, def_end_index, &eval_status); // Stacking WORD_I_JUMP_FROM

                EvalEmpiler(WORD_I_JUMP_STACK, word_dict_def_index, &eval_status); // Stacking WORD_I_JUMP_TO
                EvalEmpiler(WORD_I_JUMP_STACK, i, &eval_status); // Stacking WORD_I_JUMP_FROM

                i--;
            }
            else {
                fprintf(stderr, (char*) logger->error("Word `%s` not supported by this interpreter level."), word);
                eval_status = EVALUATION_ERROR_NOT_SUPPORTED_WORD;
            }
        }
    }

    // 

    LibererPile(WORD_I_JUMP_STACK);

    // 

    return eval_status;
}

// 

