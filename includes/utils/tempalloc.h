#pragma once

// 

#ifndef __TEMP_ALLOC_H__
#define __TEMP_ALLOC_H__

// 

#include <stdio.h>
#include <stdbool.h>

// 

typedef void* (*TEMPALLOC_ALLOCATE)(size_t __size);

// 

typedef bool (*TEMPALLOC_FREE_ALLOC)();

// 

typedef void (*TEMPALLOC_FREEALL)();

// 

/*
| /////////////////////////////////////////////////////////////////////////////////////
| /!\ This structure needs to be declared in this header to use its members as methods.
| /////////////////////////////////////////////////////////////////////////////////////
*/
typedef struct tempalloc_struct {
    TEMPALLOC_ALLOCATE allocate;
    TEMPALLOC_FREE_ALLOC freealloc;
    TEMPALLOC_FREEALL freeall;
} * TempAlloc;

// 

extern TempAlloc GetTempAlloc();

// 

#define tempalloc GetTempAlloc()

// 

#endif