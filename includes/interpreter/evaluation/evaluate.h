#pragma once

// 

#ifndef __EVALUATE_H__
#define __EVALUATE_H__

// 

#include "../../lecture.h"
#include "../../pile.h"
#include "../../dico.h"

// 

/*
|
| name: evaluate
|
| description:
|   Evaluates a given program with all required context data (language words, stack, dictionary, script dirname, debug mode, ...)
|
| arguments:
|   - <prog: Programme> - program to evaluate
|   - <dirname: char*> - path to the directory which contains the program file (required to evaluate in advanced mode (level 4) and include some other scripts)
|   - <included_word_start: int> - index of the first word of the program to evaluate
|   - <excluded_word_end: int> - index of the last word of the program before stop evaluating
|   - <eval_context_stack: Pile> - the stack used by the program while evaluating
|   - <p_eval_context_dict: Pile> - the stack used by the program while evaluating
|   - <debug: int> - the used debug mode while evaluating
|
| return <eval_status: int> - the final evaluation status (success or error code)
|
*/
extern int evaluate(Programme prog, char* dirname, int included_word_start, int excluded_word_end, int eval_word_count, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int debug);

// 

#endif