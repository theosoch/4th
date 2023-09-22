#pragma once

// 

#ifndef __STR_UTIL_H__
#define __STR_UTIL_H__

// 

#include <stdbool.h>

// 

/*
|
| name: strLength
|
| description:
|   Return the length of a given string
|
| arguments:
|   - <str1: char*> - string whose length we are looking for
|
| return <: int>
|
*/
extern int strLength(char* str);

// 

/*
|
| name: strEquals
|
| description:
|   Checks if two string are the same (have the same content)
|
| arguments:
|   - <str1: char*> - first string
|   - <str2: char*> - second string to compare with str1
|
| return <: bool>
|
*/
extern bool strEquals(char* str1, char* str2);

// 

/*
|
| name: strStartsWith
|
| description:
|   Checks if a string starts by another
|
| arguments:
|   - <str: char*> - string to check
|   - <start_str: char*> - string wich "str" must starts with
|
| return <: bool>
|
*/
extern bool strStartsWith(char* str, char* start_str);

// 

/*
|
| name: strEndsWith
|
| description:
|   Checks if a string ends by another
|
| arguments:
|   - <str: char*> - string to check
|   - <start_str: char*> - string wich "str" must ends with
|
| return <: bool>
|
*/
// extern bool strEndsWith(char* str, char* start_str);

// 

/*
|
| name: lowercase
|
| description:
|   Lowercases all characters of a string. /!\ This function doesn't copy the given string.
|
| arguments:
|   - <str: char*> - string to lowercase
|
| return <: void>
|
*/
extern char* lowercase(char* str);

// 

/*
|
| name: uppercase
|
| description:
|   Uppercases all characters of a string. /!\ This function doesn't copy the given string.
|
| arguments:
|   - <str: char*> - string to uppercase
|
| return <: void>
|
*/
extern char* lowercase(char* str);

// 

/*
|
| name: str2int
|
| description:
|   Converts a string to an integer (example : (char*) "-3" -> (int) -3), and indicates if the convertion is complete.
|
| arguments:
|   - <str: char*> - string to convert into integer
|   - <complete: bool*> - the convertion completion indicator
|
| return <: int>
|
*/
extern int str2int(char* str, bool* complete);

// 

/*
|
| name: strarrayincludes
|
| description:
|   Check if a string is included in a sub-array of a specified string array
|
| arguments:
|   - <strarray: char**> - the specified string array
|   - <included_start: int> - start index (included) of the sub-array to search in
|   - <excluded_end: int> - end index (excluded) of the sub-array to search in
|   - <str: char*> - string to search
|
| return <: int>
|
*/
extern bool strArrayIncludes(char** strarray, int included_start, int excluded_end, char* str);

// 

/*
|
| name: searchClosingWord
|
| description:
|   Search the closing word associated with an opening word and return its index (such as the associated ")" to a "(")
|
| arguments:
|   - <strarray: char**> - the specified string array
|   - <strarray_length: int> - specified string array length
|   - <word_index: int> - index of the current evaluated word
|   - <word_open: char*> - opening word (such as "(")
|   - <word_close: char*> - closing word (such as ")")
|   - <step: int> - step in the program "prog" word list
|
| return <: int> - index of the closing word "word_close" associated with opening word "word_open"
|
*/
extern int searchClosingWord(char** strarray, int strarray_length, int word_index, char* word_open, char* word_close, int step);

// 

#endif