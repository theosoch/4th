#pragma once

// 

#ifndef __LECTURE_H__
#define __LECTURE_H__

// 

#define TAILLE_MOT_MAX 32
#define NB_MOTS_MAX 2048

#define DOT_QUOTE_TEXT_MAX_LENGTH 511

// 

#define LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_COMMENT_SYNTAX 1
#define LECTURE_MODULE_ERROR_LECTURE_PROG_INVALID_MULTILINE_COMMENT_SYNTAX 2
#define LECTURE_MODULE_ERROR_LECTURE_PROG_MAX_DOT_QUOTE_TEXT_LENGTH_EXCEED 3

// 

typedef struct sProgramme * Programme;

// 

extern Programme LectureProg(char NomFichier[]);

// 

extern Programme ReadAppendProg(char* filepath, Programme prog);

// 

extern int LongueurProg(Programme Prog);

// 

extern char* MotProg(Programme Prog, int i);

// 

extern void AfficherProg(Programme Prog);

// 

extern void LibererProg(Programme Prog);

// 

/*
| //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
| /!\ After this warning, some functions has been added to be used as additionnal GETTER and SETTER of the local structure "sProgramme".
| //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

// 

/*
|
| name: ProgWordArray
|
| description:
|   Return the given program word array.
|
| arguments:
|   - <prog: Programme> - the program containing the wanted words.
|
| return <: char**> - the wanted word array.
|
*/
extern char** ProgWordArray(Programme prog);

// 

// extern int AppendProg(Programme prog_dest, Programme prog_to_append);

// 

// 

#endif