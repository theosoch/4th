#include "../../includes/utils/fileutil.h"

// 

#include <stdio.h>

// 

char* currentWorkDir() {
    return getcwd(NULL, 0);
}

// 

bool fexists(char* filepath) {
    FILE* p_file = fopen(filepath, "r");

    bool result = p_file != NULL;
    if(result) fclose(p_file);

    return result;
}

// 