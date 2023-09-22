#pragma once

// 

#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

// 

#include <stdbool.h>

// 

#if defined(_MSC_VER)
    #include <direct.h>
    #define getcwd _getcwd
#elif defined(__GNUC__)
    #include <unistd.h>
#endif

// 

extern char* currentWorkDir();

// 

/*
|
| name: fexists
|
| description:
|   Check if a file exists at the specified file path
|
| arguments:
|   - <filepath: char*> - the specified file path
|
| return <: bool>
|
*/
extern bool fexists(char* filepath);

// 

#endif