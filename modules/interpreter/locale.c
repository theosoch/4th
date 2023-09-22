#include "../../includes/interpreter/locale.h"

// 

const char* LANGUAGE_WORDS[LANGUAGE_WORD_COUNT] = {
    /*
    PILE OPERATORS
    (index range : [0;5])
    */
    ".s",
    ".",
    "dup",
    "drop",
    "swap",
    "over",
    
    /*
    ARITHMETICAL OPERATORS
    (index range : [6;10])
    */
    "+",
    "-",
    "*",
    "/",
    "mod",
    
    /*
    LOGICAL OPERATORS
    (index range [11;18])
    */
    "=",
    "<",
    "<=",
    ">",
    ">=",
    "and",
    "or",
    "not",
    
    /*
    LOGICAL COMPARATORS
    (index range [19;21])
    */
    "if",
    "else",
    "endif",

    /*
    LOOP KEYWORDS
    (index range [22;24])
    */
    "begin",
    "while",
    "repeat",

    /*
    I/O KEYWORDS
    (index range [25;32])
    */
    "emit",
    "key",
    "char",
    "cr",
    "space",
    "spaces",
    ".\"",
    "#in",

    /*
    DICTIONARY KEYWORDS
    (index range [33;35])
    */
   ":",
   ";",
   "words",

    /*
    DICTIONARY KEYWORDS
    (index range [36;36])
    */
   "include",
};

// 