#include "../../includes/utils/strutil.h"

// 

#include <stdbool.h>

// 

int strLength(char* str) {
    int len;
    for(len = 0; str[len] != '\0'; ++len);
    return len;
}

// 

bool strEquals(char* str1, char* str2) {
    int sames = true;

    int i = 0;
    for(i = 0; str1[i] != '\0' && str2[i] != '\0' && sames; ++i)
        sames = str1[i] == str2[i];

    if(sames)
        sames = str1[i] == '\0' && str2[i] == '\0';

    return sames;
}

// 

bool strStartsWith(char* str, char* start_str) {
    int starts_with = true;

    int i;
    for(i = 0; str[i] != '\0' && start_str[i] != '\0' && starts_with; ++i)
        starts_with = str[i] == start_str[i];

    if(i == 0 && start_str[0] != '\0')
        starts_with = false;

    return starts_with;
}

// 

// bool strEndsWith(char* str, char* end_str) {
//     int ends_with = true;

//     int str_length = strLength(str);
//     printf("{ %d ; `%s`\n", str_length, str);

//     int i;
//     for(i = 0; str_length-1-i > -1 && end_str[i] != '\0' && ends_with; ++i)
//         ends_with = str[str_length-1-i] == end_str[i];

//     if(i == 0 && end_str[0] != '\0')
//         ends_with = false;

//     return ends_with;
// }

// 

#define A_LC_2_A_UC_DISTANCE ((int) ('a') - (int) ('A'))

// 

char* lowercase(char* str) {
    for(int i = 0; str[i] != '\0'; ++i)
        str[i] = 'A' <= str[i] && str[i] <= 'Z' ? (char) ((int) (str[i]) + A_LC_2_A_UC_DISTANCE) : str[i];

    return str;
}

// 

char* uppercase(char* str) {
    for(int i = 0; str[i] != '\0'; ++i)
        str[i] = 'a' <= str[i] && str[i] <= 'z' ? (char) ((int) (str[i]) - A_LC_2_A_UC_DISTANCE) : str[i];

    return str;
}

// 

// bool strisint(char* str) {
//     bool is_int = true;

//     for(int i = 0; str[i] != '\0' && is_int; ++i)
//         is_int = '0' <= str[i] && str[i] <= '9';

//     return is_int;
// }

int str2int(char* str, bool* complete) {
    int sign = 1;
    int result = 0;

    int i = 0;
    if(str[i] == '-') {
        sign = -1;
        ++i;
    }

    *complete = str[i] != '\0';
    
    for(i = i; str[i] != '\0' && *complete == true; ++i) {
        *complete = '0' <= str[i] && str[i] <= '9';
        result *= 10;
        result += ((int) (str[i]) - (int) ('0'));
    }

    return sign * result;
}

// 

bool strArrayIncludes(char** strarray, int included_start, int excluded_end, char* str) {
    bool found = false;

    for(int i = included_start; i < excluded_end && !found; ++i)
        found = strEquals(strarray[i], str);

    return found;
}

// 

int searchClosingWord(char** strarray, int strarray_length, int word_index, char* word_open, char* word_close, int step) {
    int closing_indicator = 1;

    char* word;
    int i;
    for(i = word_index+step; closing_indicator != 0 && 0 <= i && i < strarray_length; i += step) {
        word = strarray[i];

        if(strEquals(word, word_open))
            closing_indicator += 1;
        else if(strEquals(word, word_close))
            closing_indicator -= 1;
    }

    if(closing_indicator != 0)
        return -1;

    if(i != word_index+step)
        i += -step;

    return i;
}

// 