#pragma once

// 

#ifndef __LEVEL1_H__
#define __LEVEL1_H__

// 

#include "../../lecture.h"
#include "../../pile.h"

// 

/*
|
| name: EVALUATE_LEVEL_1
|
| description:
|   First level of evaluation with only the basic language words ("basic" mode of the interpeter)
|
| arguments:
|   - <prog: Programme> - program to evaluate
|   - <included_word_start: int> - index of the first word of the program to evaluate
|   - <excluded_word_end: int> - index of the last word of the program before stop evaluating
|   - <eval_context_stack: Pile> - the stack used by the program while evaluating
|
| return <eval_status: int> - the final evaluation status (success or error code)
|
*/
extern int EVALUATE_LEVEL_1(Programme prog, int included_word_start, int excluded_word_end, Pile eval_context_stack);

// 

#endif