#include "../../includes/utils/tempalloc.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../../includes/memoire.h"

// 

static void* TEMPALLOC_ALLOC_BUFFER[65536];
static int TEMPALLOC_ALLOC_BUFFER_LENGTH = 0;

// 

static void* __tempalloc_allocate__(size_t __size) {
    void* addr = Allouer(__size);

    if(addr != NULL) {
        TEMPALLOC_ALLOC_BUFFER[TEMPALLOC_ALLOC_BUFFER_LENGTH] = addr;
        TEMPALLOC_ALLOC_BUFFER_LENGTH++;
    }
    
    return addr;
}

// 

static bool __tempalloc_free_alloc__(void* addr) {
    int addr_index = -1;
    for(int i = 0; i < TEMPALLOC_ALLOC_BUFFER_LENGTH && addr_index < 0; ++i) {
        if(TEMPALLOC_ALLOC_BUFFER[i] == addr) {
            addr_index = i;
        }
    }

    if(addr_index < 0)
        return false;

    Liberer(addr);
    TEMPALLOC_ALLOC_BUFFER[addr_index] = TEMPALLOC_ALLOC_BUFFER[TEMPALLOC_ALLOC_BUFFER_LENGTH-1];
    TEMPALLOC_ALLOC_BUFFER[TEMPALLOC_ALLOC_BUFFER_LENGTH-1] = NULL;
    TEMPALLOC_ALLOC_BUFFER_LENGTH--;

    return true;
}

// 

static void __tempalloc_free_all__() {
    void* addr;

    for(int i = 0; i < TEMPALLOC_ALLOC_BUFFER_LENGTH; ++i) {
        addr = TEMPALLOC_ALLOC_BUFFER[i];
        
        if(addr != NULL)
            Liberer(addr);

        TEMPALLOC_ALLOC_BUFFER[i] = NULL;
    }

    TEMPALLOC_ALLOC_BUFFER_LENGTH = 0;
}

// 

static TempAlloc _tempalloc = NULL;

TempAlloc GetTempAlloc() {
    _tempalloc = _tempalloc == NULL ? __tempalloc_allocate__( sizeof(struct tempalloc_struct) * 1 ) : _tempalloc;

    _tempalloc->allocate = __tempalloc_allocate__;
    _tempalloc->freealloc = __tempalloc_free_alloc__;
    _tempalloc->freeall = __tempalloc_free_all__;

    return _tempalloc;
}

// 

#define tempalloc GetTempAlloc()

// 