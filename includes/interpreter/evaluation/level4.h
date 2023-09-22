#pragma once

// 

#ifndef __LEVEL4_H__
#define __LEVEL4_H__

// 

#include "../../lecture.h"
#include "../../pile.h"
#include "../../dico.h"

// 

/*
|
| name: EVALUATE_LEVEL_4
|
| description:
|   Forth level of evaluation with only the advanced language words ("advanced" mode of the interpeter)
|
| arguments:
|   - <prog: Programme> - program to evaluate
|   - <dirname: char*> - path to the directory which contains the program file (required to include some other scripts)
|   - <included_word_start: int> - index of the first word of the program to evaluate
|   - <excluded_word_end: int> - index of the last word of the program before stop evaluating
|   - <eval_context_stack: Pile> - the stack used by the program while evaluating
|   - <p_eval_context_dict: Pile> - the stack used by the program while evaluating
|
| return <eval_status: int> - the final evaluation status (success or error code)
|
*/
extern int EVALUATE_LEVEL_4(Programme prog, char* dirname, int included_word_start, int excluded_word_end, Pile eval_context_stack, Dictionnaire* p_eval_context_dict);

// 

#endif