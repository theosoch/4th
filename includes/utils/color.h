#pragma once

// 

#ifndef __COLOR_H__
#define __COLOR_H__

// 

#define ESCAPE_CODE_START "\x1b["
#define ESCAPE_CODE_START_LENGTH 2

#define ESCAPE_CODE_START_COLOR_DEBUG "E["
#define ESCAPE_CODE_START_COLOR_DEBUG_LENGTH 2

#define ESCAPE_CODE_END "m"
#define ESCAPE_CODE_END_LENGTH 1

// 

#define ESCAPE_CODE_RGB_IDENTIFIER "38;2;"
#define ESCAPE_CODE_RGB_IDENTIFIER_LENGTH 5

// 

#define COLOR_CASE '&'

// 

#define RGB_CASE '#'

// 

extern unsigned long hexstr2dec(char* str);

// 

extern char* color(char* str);

// 

extern char* colordebug(char* str);

// 

extern char* unescape(char* str);

// 

#endif