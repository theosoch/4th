#include "../../includes/utils/pathutil.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../../includes/utils/tempalloc.h"
#include "../../includes/utils/strutil.h"

#include "../../includes/memoire.h"

// 

#define PATH_RESOLVE_FRAGMENTS_MAX 65536

char* pathResolve(char* p) {
    int p_length = strLength(p);

    int result_length = 0;

    // 

    int path_fragment_count = 0;
    int path_fragment_char_i = 0;
    char* path_fragment_array[PATH_RESOLVE_FRAGMENTS_MAX];
    int path_fragment_length_array[PATH_RESOLVE_FRAGMENTS_MAX];
    
    char c;

    path_fragment_array[path_fragment_count] = Allouer( sizeof(char) * (FILENAME_MAX+1) );
    path_fragment_array[path_fragment_count][0] = '\0';

    int root_depth_level = 0;

    for(int i = 0; i < p_length+1; ++i) {
        c = p[i];
        if(
            (c == '/' || c == '\\' || c == '\0')
         ) {
            path_fragment_array[path_fragment_count][path_fragment_char_i] = '\0';
            path_fragment_length_array[path_fragment_count] = path_fragment_char_i;

            result_length += path_fragment_length_array[path_fragment_count]+1;
            
            if(path_fragment_array[path_fragment_count][0] == '.') {
                if(root_depth_level > 0) {
                    Liberer(path_fragment_array[path_fragment_count]);
                    result_length -= path_fragment_length_array[path_fragment_count]+1;
                    
                    if(path_fragment_array[path_fragment_count][1] == '.') {
                        path_fragment_count--;

                        Liberer(path_fragment_array[path_fragment_count]);
                        result_length -= path_fragment_length_array[path_fragment_count]+1;
                    }
                    
                    path_fragment_count--;
                    root_depth_level--;
                }
            }
            else
                root_depth_level++;

            path_fragment_count++;
            path_fragment_char_i = 0;

            if(path_fragment_count < PATH_RESOLVE_FRAGMENTS_MAX) {
                path_fragment_array[path_fragment_count] = Allouer( sizeof(char) * (FILENAME_MAX+1) );
                path_fragment_array[path_fragment_count][0] = '\0';
            }
        }
        else {
            path_fragment_array[path_fragment_count][path_fragment_char_i] = c;
            path_fragment_char_i++;
        }
    }

    if(path_fragment_count < PATH_RESOLVE_FRAGMENTS_MAX && path_fragment_array[path_fragment_count] != NULL)
        Liberer(path_fragment_array[path_fragment_count]);

    result_length--;
    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );

    int k = 0;
    for(int i = 0; i < path_fragment_count; ++i) {
        int j;
        for(j = 0; j < path_fragment_length_array[i]; ++j) {
            result[k+j] = path_fragment_array[i][j];
        }

        if(i+1 < path_fragment_count)
            result[k+j] = '/';

        k += path_fragment_length_array[i]+1;
        Liberer(path_fragment_array[i]);
    }

    result[result_length] = '\0';

    return result;
}

// 

char* pathDirname(char* p) {
    int separator_last_index = -1;

    for(int i = 0; p[i] != '\0'; ++i) {
        if(p[i] == '/' || p[i] == '\\') {
            separator_last_index = i;
        }
    }

    int result_length = separator_last_index+1;
    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );
    
    for(int i = 0; i < result_length; ++i)
        result[i] = p[i];
    result[result_length] = '\0';

    return result;
}

// 

char* pathJoin(char* p1, char* p2) {
    int p1_length = strLength(p1);
    int p2_length = strLength(p2);

    int p1_file_separator_missing = p1[p1_length-1] != '/' && p1[p1_length-1] != '\\';
    int p2_starts_with_file_separator = p2[0] == '/' || p2[0] == '\\';
    
    int result_length = p1_length+p2_length + p1_file_separator_missing - p2_starts_with_file_separator;

    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );

    for(int i = 0; i < p1_length; ++i)
        result[i] = p1[i];
    
    if(p1_file_separator_missing) result[p1_length] = '/';

    for(int i = p2_starts_with_file_separator; i < p2_length; ++i)
        result[i-p2_starts_with_file_separator+(p1_length+p1_file_separator_missing)] = p2[i];
    
    result[result_length] = '\0';

    return result;
}

// 