#pragma once

// 

#ifndef __CLI_H__
#define __CLI_H__

// 

#include "../pile.h"
#include "../dico.h"

// 

/*
|
| name: cli
|
| description:
|   "Command Line Interpreter" (CLI) : this function evaluates and returns the interpretation of a forth script
|
| arguments:
|   - <int: argc> - command line argument count from the main
|   - <int: argv> - command line arguments from the main
|   - <eval_context_stack: Pile> - the evaluation context stack to use
|   - <p_eval_context_dict: Dictionnaire*> - pointer to the evaluation context dictionary to use
|
| return <eval_status: int>
|
*/
extern int cli(int argc, char** argv, Pile eval_context_stack, Dictionnaire* p_eval_context_dict, int* p_debuglevel);

// 

#endif