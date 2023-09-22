#include "../includes/lecture.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../includes/utils/logger.h"

#include "../includes/utils/strutil.h"
#include "../includes/interpreter/locale.h"

#include "../includes/memoire.h"

// 

struct sProgramme {
    int NbMots;
    char * TabMots[NB_MOTS_MAX];
};

// 

Programme LectureProg(char NomFichier[]) {
    Programme result = NULL;
    Programme prog = Allouer( sizeof(struct sProgramme) * 1 );

    if(prog == NULL) {
        fprintf(stderr, logger->error("Unable to allocate the new program."));
        return NULL;
    }

    // 

    result = ReadAppendProg(NomFichier, prog);

    if(result == NULL)
        LibererProg(prog);

    return result;
}

Programme ReadAppendProg(char* filepath, Programme prog) {
    FILE* p_file = fopen(filepath, "r");

    if(p_file == NULL) {
        fprintf(stderr, logger->error("Unable to open file `%s`."), filepath);
        return NULL;
    }

    // 

    int error_code = 0;

    // 

    int word_count = LongueurProg(prog);

    if(word_count >= NB_MOTS_MAX)
        return NULL;

    prog->TabMots[word_count] = Allouer( sizeof(char) * (TAILLE_MOT_MAX+1) );

    bool in_forth_comment = false;

    int if_else_enclosures = 0;
    int if_endif_enclosures = 0;
    
    int begin_while_enclosures = 0;
    int begin_repeat_enclosures = 0;
    
    int def_word_start_end_enclosures = 0;

    int file_reading_state = 0;
    char c = '\1';
    char c1 = '\1';
    int w_i = 0;
    int w_l = 0;

    // 

    while(
        word_count < NB_MOTS_MAX
        && (file_reading_state = fscanf(p_file, "%s", prog->TabMots[word_count])) != EOF
        && !(error_code > 0)
    ) {
        lowercase(prog->TabMots[word_count]);
        
        if(strEquals(prog->TabMots[word_count], ")"))
            error_code = LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_COMMENT_SYNTAX;
        else if(strEquals(prog->TabMots[word_count], "*)"))
            error_code = LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_MULTILINE_COMMENT_SYNTAX;
        else {
            if((in_forth_comment = strEquals(prog->TabMots[word_count], "("))) {
                while(file_reading_state != EOF && c != ')' && c != '\n') {
                    file_reading_state = (c = fgetc(p_file)) == EOF ? EOF : 0;
                }
                
                if(file_reading_state == EOF)
                    error_code = LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_COMMENT_SYNTAX;
            }
            else if((in_forth_comment = strEquals(prog->TabMots[word_count], "\\"))) {
                while(file_reading_state != EOF && c != '\n') {
                    file_reading_state = (c = fgetc(p_file)) == EOF ? EOF : 0;
                }
            }
            else if((in_forth_comment = strEquals(prog->TabMots[word_count], "(*"))) {
                while(file_reading_state != EOF && !(c == ')' && c1 == '*')) {
                    c1 = c;
                    file_reading_state = (c = fgetc(p_file)) == EOF ? EOF : 0;
                }

                if(file_reading_state == EOF)
                    error_code = LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_MULTILINE_COMMENT_SYNTAX;                
            }

            // 

            if(in_forth_comment) {
                Liberer(prog->TabMots[word_count]);
                word_count--;
                c = '\1';
                c1 = '\1';
                in_forth_comment = false;
            }
            else {
                c = '\1';

                // last_word == ".\""
                if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[31])) {
                    word_count++;

                    w_l = DOT_QUOTE_TEXT_MAX_LENGTH;
                    prog->TabMots[word_count] = Allouer( sizeof(char) * (w_l+1) );
                
                    file_reading_state = (c = fgetc(p_file)) == EOF;
                    for(w_i = 0; file_reading_state != EOF && c != '"' && w_i < w_l; ++w_i) {
                        file_reading_state = (c = fgetc(p_file)) == EOF;
                        prog->TabMots[word_count][w_i] = c;
                    }

                    if(w_i < w_l)
                        prog->TabMots[word_count][w_i-1] = '\0';
                    else {
                        prog->TabMots[word_count][w_i] = '\0';

                        file_reading_state = (c = fgetc(p_file)) == EOF;
                        if(c != '"')
                            error_code = LECTURE_MODULE_ERROR_LECTURE_PROG_MAX_DOT_QUOTE_TEXT_LENGTH_EXCEED;
                    }
                }
                // last_word == "include"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[36])) {
                    w_l = FILENAME_MAX-1;

                    Liberer(prog->TabMots[word_count]);
                    prog->TabMots[word_count] = Allouer( sizeof(char) * (w_l+1) );
                
                    for(w_i = 0; LANGUAGE_WORDS[36][w_i] != '\0'; ++w_i)
                        prog->TabMots[word_count][w_i] = LANGUAGE_WORDS[36][w_i];

                    prog->TabMots[word_count][w_i] = '\0';
                    file_reading_state = fscanf(p_file, "%s ", (prog->TabMots[word_count])+w_i+1);
                    prog->TabMots[word_count][w_i] = '\0';
                }

                // last_word == "if"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[19])) {
                    if_else_enclosures++;
                    if_endif_enclosures++;
                }
                // last_word == "else"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[20]))
                    if_else_enclosures--;
                // last_word == "endif"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[21]))
                    if_endif_enclosures--;
                // last_word == "begin"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[22])) {
                    begin_while_enclosures++;
                    begin_repeat_enclosures++;
                }

                // last_word == "while"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[23]))
                    begin_while_enclosures--;
                // last_word == "repeat"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[24]))
                    begin_repeat_enclosures--;
                // last_word == "while"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[23]))
                    begin_while_enclosures--;
                
                // last_word == ":"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[33])) {
                    // last_word != "char"
                    if(
                        (
                            word_count > 0
                            && !strEquals(prog->TabMots[word_count-1], (char*) LANGUAGE_WORDS[27])
                        )
                        || word_count == 0
                    ) {
                        def_word_start_end_enclosures++;
                    }
                }
                // last_word == ";"
                else if(strEquals(prog->TabMots[word_count], (char*) LANGUAGE_WORDS[34]))
                    def_word_start_end_enclosures--;
            }
        }

        // 

        word_count++;

        if(word_count < NB_MOTS_MAX)
            prog->TabMots[word_count] = Allouer( sizeof(char) * (TAILLE_MOT_MAX+1) );
    }

    // 

    if(word_count < NB_MOTS_MAX)
        Liberer(prog->TabMots[word_count]);

    prog->NbMots = word_count;

    // 

    fclose(p_file);

    // 

    if(error_code != 0) {
        if(error_code == LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_COMMENT_SYNTAX)
            fprintf(stderr, logger->error("Invalid comment syntax : check if your comment is on a single line and starts with `( ` (the word `(` ) and ends with `)` (as character)."));
        else if(error_code == LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_MULTILINE_COMMENT_SYNTAX)
            fprintf(stderr, logger->error("Invalid multiline comment syntax : check if your comment is a block of words `(*` and `*)`."));
        else if(error_code == LECTURE_MODULE_ERROR_LECTURE_PROG_MAX_DOT_QUOTE_TEXT_LENGTH_EXCEED)
            fprintf(stderr, logger->error("Bad `.\"` keyword usage : the following text shouldn't exceed %d characters."), DOT_QUOTE_TEXT_MAX_LENGTH);

        return NULL;
    }
    else {
        int needs_cancel_reading = false;

        if((needs_cancel_reading = if_else_enclosures < 0))
            fprintf(stderr, logger->error("Invalid logical control structure syntax : missing %d `if` keyword(s)."), if_else_enclosures*(-1));
        else if((needs_cancel_reading = if_endif_enclosures > 0))
            fprintf(stderr, logger->error("Invalid logical control structure syntax : missing %d `endif` keyword(s)."), if_endif_enclosures);
        else if((needs_cancel_reading = if_endif_enclosures < 0))
            fprintf(stderr, logger->error("Invalid logical control structure syntax : missing %d `endif` keyword(s)."), if_endif_enclosures*(-1));
        else if((needs_cancel_reading = begin_while_enclosures > 0))
            fprintf(stderr, logger->error("Invalid loop control structure syntax : missing %d `while` keyword(s)."), begin_while_enclosures);
        else if((needs_cancel_reading = begin_while_enclosures < 0))
            fprintf(stderr, logger->error("Invalid loop control structure syntax : missing %d `begin` keyword(s)."), begin_while_enclosures*(-1));
        else if((needs_cancel_reading = begin_repeat_enclosures > 0))
            fprintf(stderr, logger->error("Invalid loop control structure syntax : missing %d `repeat` keyword(s)."), begin_repeat_enclosures);
        else if((needs_cancel_reading = begin_repeat_enclosures < 0))
            fprintf(stderr, logger->error("Invalid loop control structure syntax : missing %d `begin` keyword(s)."), begin_repeat_enclosures*(-1));
        else if((needs_cancel_reading = def_word_start_end_enclosures > 0))
            fprintf(stderr, logger->error("Invalid new word definition syntax : missing %d `;` keyword(s)."), def_word_start_end_enclosures);
        else if((needs_cancel_reading = def_word_start_end_enclosures < 0))
            fprintf(stderr, logger->error("Invalid new word definition syntax : missing %d `:` keyword(s)."), def_word_start_end_enclosures*(-1));

        if(needs_cancel_reading)
            return NULL;
    }

    // 

    return prog;
}

// 

int LongueurProg(Programme Prog) {
    return Prog->NbMots;
}

// 

char* MotProg(Programme Prog, int i) {
    return Prog->TabMots[i];
}

// 

void AfficherProg(Programme Prog) {
    int prog_size = LongueurProg(Prog);
    if(prog_size == 1) {

    }
    else {
        for(int i = 0; i < prog_size; ++i) {
            if(i == 0)
                printf("╔╾");
            else if(i == prog_size-1)
                printf("╚╾");
            else
                printf("╠╾");
            printf("[%d] `%s`\n", i, MotProg(Prog, i));
        }
    }
}

// 

void LibererProg(Programme Prog) {
    int prog_size = LongueurProg(Prog);
    for(int i = 0; i < prog_size; ++i) {
        char* m = MotProg(Prog, i);
        if(m != NULL)
            Liberer(m);
    }

    Liberer(Prog);
}

// 

// ////////////////////////////////////////////////////////////////

// 

char** ProgWordArray(Programme prog) {
    return (char**) prog->TabMots;
}

// 

// int ProgAllocateCustomNewWord(Programme prog, int size) {
//     if(LongueurProg(prog) >= NB_MOTS_MAX)
//         return -1;

//     char* word_addr = Allouer( sizeof(char) * (size+1) );

//     if(word_addr == NULL)
//         return 0;

//     ProgWordArray(prog)[LongueurProg(prog)] = word_addr;

//     prog->NbMots++;

//     return 1;
// }

// 

// int AppendProg(Programme prog_dest, Programme prog_to_append) {
//     int prog_to_append_size = LongueurProg(prog_to_append);
    
//     char c;
//     char* word;

//     int word_end_count;
//     int word_end_count_max;

//     int status = 1;

//     for(int i = 0; i < prog_to_append_size && LongueurProg(prog_dest) < NB_MOTS_MAX && status > 0; ++i) {
        
//         word = MotProg(prog_to_append, i);

//         word_end_count_max = 1;

//         // word == "include"
//         if(strEquals(word, (char*) LANGUAGE_WORDS[36])) {
//             status = ProgAllocateCustomNewWord(prog_dest, strLength((char*) LANGUAGE_WORDS[36])+1+FILENAME_MAX-1);
//             word_end_count_max++;
//         }
//         else
//             status = ProgAllocateCustomNewWord(prog_dest, TAILLE_MOT_MAX);

//         c = '\1';
//         word_end_count = 0;
//         for(int j = 0; word_end_count < word_end_count_max; ++j) {
//             if(c == '\0')
//                 word_end_count++;

//             if(word_end_count < word_end_count_max) {
//                 c = word[j];
//                 MotProg(prog_dest, LongueurProg(prog_dest)-1)[j] = c;
//             }
//         }
//     }

//     return status;
// }