#pragma once

// 

#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

// 

#include <stdbool.h>

// 

#include "../../lecture.h"
#include "../../pile.h"
#include "../../dico.h"

// 

/*
|
| name: validateProgram
|
| description:
|   Checks if a program is valid or not
|
| arguments:
|   - <prog: Programme> - program to check
|
| return <valid: bool>
|
*/
extern bool validProgram(Programme prog, char** eval_words, int eval_word_count);

// 

/*
|
| name: EvalEmpiler
|
| description:
|   Try to stack an element on top of the used evaluation context stack and change the evaluation status when an error happened.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <Elt: int> - element to stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EvalEmpiler(Pile eval_context_stack, int Elt, int* p_eval_status);

// 

/*
|
| name: EvalDepiler
|
| description:
|   Try to unstack the top of the used evaluation context stack and change the evaluation status when an error happened.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern int EvalDepiler(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_DOT_S
|
| description:
|   Evaluates the keyword ".s" : prints the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|
| return <: void>
|
*/
extern void EVAL_DOT_S(Pile eval_context_stack);

// 

/*
|
| name: EVAL_DOT
|
| description:
|   Evaluates the keyword "." : unstacks and prints the top value of the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_DOT(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_DUP
|
| description:
|   Evaluates the keyword "dup" : duplicates the top value of the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_DUP(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_DROP
|
| description:
|   Evaluates the keyword "drop" : unstacks the top value of the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_DROP(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_SWAP
|
| description:
|   Evaluates the keyword "swap" : swaps the top value with the under-top value of the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_SWAP(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_OVER
|
| description:
|   Evaluates the keyword "over" : duplicates the under-top value of the used evaluation context stack
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_OVER(Pile eval_context_stack, int* p_eval_status);

// ARITHMETICAL OPERATIONS

#define ARITHMETICAL_OPERATION_ADD 0
#define ARITHMETICAL_OPERATION_SUBSTRACT 1
#define ARITHMETICAL_OPERATION_MULTIPLY 2
#define ARITHMETICAL_OPERATION_DIVIDE 3
#define ARITHMETICAL_OPERATION_MODULO 4

/*
|
| name: EVAL_ARITHMETICAL_OPERATION
|
| description:
|   Evaluates a specified arithmetical operation keyword
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <operation: int> - the arithmetical operation to evaluate
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_ARITHMETICAL_OPERATION(Pile eval_context_stack, int operation, int* p_eval_status);

// LOGICAL OPERATIONS

#define LOGICAL_OPERATION_EQUAL 0
#define LOGICAL_OPERATION_LESSER 1
#define LOGICAL_OPERATION_LESSER_OR_EQUAL 2
#define LOGICAL_OPERATION_GREATER 3
#define LOGICAL_OPERATION_GREATER_OR_EQUAL 4
#define LOGICAL_OPERATION_AND 5
#define LOGICAL_OPERATION_OR 6
#define LOGICAL_OPERATION_NOT 7

/*
|
| name: EVAL_LOGICAL_OPERATION
|
| description:
|   Evaluates a specified logical operation keyword
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <operation: int> - the logical operation to evaluate
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_LOGICAL_OPERATION(Pile eval_context_stack, int operation, int* p_eval_status);

// 

/*
|
| name: EVAL_LOGICAL_CONTROL_IF
|
| description:
|   Evaluates the logical comparison keyword "if" and its associated keywords "else" and "endif" and change the evaluation status when an error happened.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <eval_words: const char**> - the list of the used language words in the evaluation context
|   - <prog: Programme> - the used program
|   - <prog_size: int> - size of / word count of the used program
|   - <word_index: int> - index of the current evaluated word
|   - <WORD_I_JUMP_STACK: Pile> - the temporary storage stack to jump from a word to another during the program evaluation
|                                 [!] required to skip the first or the second instruction block and for multilayer logical comparisons
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_LOGICAL_CONTROL_IF(Pile eval_context_stack, const char** eval_words, Programme prog, int prog_size, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status);

// 

/*
|
| name: EVAL_LOOP_CONTROL_WHILE
|
| description:
|   Evaluates the lopp keyword "while" and its associated keywords "begin" and "repeat" and change the evaluation status when an error happened.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <eval_words: const char**> - the list of the used language words in the evaluation context
|   - <prog: Programme> - the used program
|   - <prog_size: int> - size of / word count of the used program
|   - <word_index: int> - index of the current evaluated word
|   - <WORD_I_JUMP_STACK: Pile> - the temporary storage stack to jump from a word to another during the program evaluation
|                                 [!] required to go back to the "begin" instruction block or skip and leave a loop and for multilayer loops
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_LOOP_CONTROL_WHILE(Pile eval_context_stack, const char** eval_words, Programme prog, int prog_size, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status);

// 

/*
|
| name: EVAL_EMIT
|
| description:
|   Evaluates the keyword "emit" : print the char corresponding to the number on top of the evaluation context stack according to the ASCII table.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_EMIT(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_KEY
|
| description:
|   Evaluates the keyword "key" : waits for user to input a key into the terminal.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_KEY(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_CHAR
|
| description:
|   Evaluates the keyword "char" : gets the corresponding ASCII code of the following character and stacks it on top of the evaluation context stack.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_CHAR(Pile eval_context_stack, Programme prog, int prog_size, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status);

// 

/*
|
| name: EVAL_CR
|
| description:
|   Evaluates the keyword "cr" : as its name means, it prints a carriage return ("\n").
|
| arguments:
|   (no argument)
|
| return <: void>
|
*/
extern void EVAL_CR();

// 

/*
|
| name: EVAL_CR
|
| description:
|   Evaluates the keyword "cr" : as its name means, it prints a simple space (" ").
|
| arguments:
|   (no argument)
|
| return <: void>
|
*/
extern void EVAL_SPACE();

// 

/*
|
| name: EVAL_CR
|
| description:
|   Evaluates the keyword "cr" : prints the number of spaces corresponding to the number on top of the evaluation context stack.
|
| arguments:
|   (no argument)
|
| return <: void>
|
*/
extern void EVAL_SPACES(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_CHAR
|
| description:
|   Evaluates the keyword ".\"" : prints the following characters until the next '"'.
|
| arguments:
|   - <prog: Programme> - the evaluated program
|   - <excluded_word_end: int> - the excluded last word evaluated of the program
|   - <word_index: int> - the the current word's index
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_DOT_QUOTE(Programme prog, int excluded_word_end, int word_index, Pile WORD_I_JUMP_STACK, int* p_eval_status);

// 

/*
|
| name: EVAL_INTEGER_INPUT
|
| description:
|   Evaluates the keyword "#in" : waits for user to input an integer and stacks it on top of the evaluation context stack.
|
| arguments:
|   - <eval_context_stack: Pile> - the used evaluation context stack
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_INTEGER_INPUT(Pile eval_context_stack, int* p_eval_status);

// 

/*
|
| name: EVAL_WORD_DEFINITION
|
| description:
|   Evaluates the keyword "#in" : waits for user to input an integer and stacks it on top of the evaluation context stack.
|
| arguments:
|   - <prog: Programme> - the evaluated program
|   - <prog_size: int> - size of the evaluated program
|   - <eval_words: const char**> - used evaluation words by the intepreter level
|   - <eval_word_count: int> - count of used evaluation words by the intepreter level
|   - <word_index: int> - current word's index
|   - <WORD_I_JUMP_STACK: Pile> - the used stack to jump between words of the program in the evaluation loop.
|   - <p_eval_context_dict: Dictionnaire*> - pointer to the used evaluation context dictionary
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_WORD_DEFINITION(Programme prog, int prog_size, const char** eval_words, int eval_word_count, int word_index, Pile WORD_I_JUMP_STACK, Dictionnaire* p_eval_context_dict, int* p_eval_status);

// 

/*
|
| name: EVAL_WORD_DEFINITION
|
| description:
|   Evaluates the keyword "words" : prints all defined words in the eval context dictionary
|
| arguments:
|   - <p_eval_context_dict: Dictionnaire*> - pointer to the used evaluation context dictionary
|
| return <: void>
|
*/
extern void EVAL_WORDS_KEYWORD(Dictionnaire* p_eval_context_dict);

// 

/*
|
| name: EVAL_INCLUDE
|
| description:
|   Evaluates the keyword "INCLUDE" : includes the program at the indicated filepath and copy its words into the current program.
|
| arguments:
|   - <prog: Programme> - the evaluated program
|   - <dirname: char*> - path to the directory of the evaluated program/script file
|   - <excluded_word_end: int> - the excluded last word evaluated of the program
|   - <eval_words: const char**> - used evaluation words by the intepreter level
|   - <eval_word_count: int> - count of used evaluation words by the intepreter level
|   - <word_index: int> - current word's index
|   - <WORD_I_JUMP_STACK: Pile> - the used stack to jump between words of the program in the evaluation loop.
|   - <p_eval_context_dict: Dictionnaire*> - pointer to the used evaluation context dictionary
|   - <p_eval_status: int*> - pointer to the evaluation status address
|
| return <: void>
|
*/
extern void EVAL_INCLUDE(Programme prog, char* dirname, int excluded_word_end, const char** eval_words, int eval_word_count, int word_index, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int* p_eval_status);

// 

#endif