#include "../../includes/utils/color.h"

// 



// 

#include "../../includes/utils/tempalloc.h"

#include "../../includes/memoire.h"

// 

const char CC_BOLD[2] = { 'l', '1' };
const char CC_STRIKETHROUGH[2] = { 'm', '9' };
const char CC_UNDERLINE[2] = { 'n', '4' };
const char CC_ITALIC[2] = { 'o', '3' };
const char CC_RESET[2] = { 'r', '0' };

// 

const char CC_BLACK[3] = { '0', '3','0' };
const char CC_DARK_BLUE[3] = { '1', '3','4' };
const char CC_DARK_GREEN[3] = { '2', '3','2' };
const char CC_DARK_AQUA[3] = { '3', '3','6' };
const char CC_DARK_RED[3] = { '4', '3','1' };
const char CC_DARK_PURPLE[3] = { '5', '3','5' };
const char CC_GOLD[3] = { '6', '3','3' };
const char CC_GRAY[3] = { '7', '3','7' };
const char CC_DARK_GRAY[3] = { '8', '9','0' };
const char CC_BLUE[3] = { '9', '9','4' };
const char CC_GREEN[3] = { 'a', '9','2' };
const char CC_AQUA[3] = { 'b', '9','6' };
const char CC_RED[3] = { 'c', '9','1' };
const char CC_LIGHT_PURPLE[3] = { 'd', '9','5' };
const char CC_YELLOW[3] = { 'e', '9','3' };
const char CC_WHITE[3] = { 'f', '9','7' };

// 

static int COLOR_DEBUG = 0;

// 

unsigned long hexstr2dec(char* str) {
    char c = '\1';

    int result = 0;

    unsigned long str_len;
    for(str_len = 0; (c = str[str_len]) != '\0'; ++str_len);

    int p = 1;
    for(int i = str_len-1; i > -1; --i) {
        c = str[i];
        if(c >= '0' && c <= '9')
            result += ((int) (c) - (int) ('0')) * p;
        if(c >= 'a' && c <= 'f')
            result += ((int) (c) - (int) ('a') + 10) * p;
        p *= 16;
    }

    return result;
}

// 

char* color(char* str) {
    int result_length = 0;

    char c = '\1';

    int check_color_case = 0;

    // CALCULATING RESULT LENGTH :

    for(int i = 0; c != '\0'; ++i) {
        c = str[i];
        
        if(check_color_case) {
            result_length += COLOR_DEBUG ? ESCAPE_CODE_START_COLOR_DEBUG_LENGTH : ESCAPE_CODE_START_LENGTH;
            
            if(c == RGB_CASE) {
                result_length += ESCAPE_CODE_RGB_IDENTIFIER_LENGTH + (3*3) + (3-1);
                i += 6;
            }
            else {
                if(
                    (c >= '0' && c <= '9')
                    || (c >= 'a' && c <= 'f')
                )
                    result_length += 1;
                result_length += 1;
                i += 1;
            }

            result_length += ESCAPE_CODE_END_LENGTH;
            
            check_color_case = 0;
        }
        else
            result_length += 1;

        c = str[i];
        check_color_case = c == COLOR_CASE;
    }
    result_length--;

    result_length += (COLOR_DEBUG ? ESCAPE_CODE_START_COLOR_DEBUG_LENGTH : ESCAPE_CODE_START_LENGTH) + 1 + ESCAPE_CODE_END_LENGTH;

    // 

    // ALLOCATION SPACE FOR RESULT :

    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );
    for(int i = 0; i < result_length; ++i)
        result[i] = '-';
    result[result_length] = '\0';

    //

    // FORMATTING COLOR CODES - "Replace" all color cases by corresponding escape codes into result :

    static char rgb_hexstr_tmp[3];
    static int rgb[3];
    static int rgb_reverse[3] = { 0, 0, 0 };

    c = '\1';
    char c2 = '\1';
    int _i = 0;
    int k = 0;

    for(int i = 0; c != '\0'; ++i, ++_i) {
        c = str[i];
        
        if(check_color_case) {
            k = _i-1;

            // 

            if(COLOR_DEBUG) {
                for(int j = 0; j < ESCAPE_CODE_START_COLOR_DEBUG_LENGTH; ++j)
                    result[k+j] = ESCAPE_CODE_START_COLOR_DEBUG[j];
                k += ESCAPE_CODE_START_COLOR_DEBUG_LENGTH;
            }
            else {
                for(int j = 0; j < ESCAPE_CODE_START_LENGTH; ++j)
                    result[k+j] = ESCAPE_CODE_START[j];
                k += ESCAPE_CODE_START_LENGTH;
            }

            // 

            if(c == RGB_CASE) {
                for(int j = 0; j < ESCAPE_CODE_RGB_IDENTIFIER_LENGTH; ++j)
                    result[k+j] = ESCAPE_CODE_RGB_IDENTIFIER[j];
                k += ESCAPE_CODE_RGB_IDENTIFIER_LENGTH;

                rgb_reverse[0] = 0;
                rgb_reverse[1] = 0;
                rgb_reverse[2] = 0;
                for(int m = 0; m < 3; ++m) {
                    for(int j = 0; j < 2; ++j) {
                        rgb_hexstr_tmp[j] = str[i+(2*m)+j+1];
                    }

                    rgb_hexstr_tmp[2] = '\0';
                    rgb[m] = hexstr2dec(rgb_hexstr_tmp);

                    int p = 100;
                    for(int j = rgb[m], n = 0; n < 3; ++n) {
                        rgb_reverse[m] += (j % 10) * p;
                        j = (int) (j / 10);
                        p = p / 10;
                    }

                    for(int j = rgb_reverse[m], n = 0; n < 3; ++n) {
                        result[k] = (char) ((int) ('0') + (j % 10));
                        j = (int) (j / 10);
                        k++;
                    }
                    result[k] = ';';
                    k++;
                }
                k--;
                i += 1 + 6;
            }
            else {
                i++;
                c2 = str[i-1];
                
                if(c2 == CC_BOLD[0])
                    result[k] = CC_BOLD[1];
                else if(c2 == CC_STRIKETHROUGH[0])
                    result[k] = CC_STRIKETHROUGH[1];
                else if(c2 == CC_UNDERLINE[0])
                    result[k] = CC_UNDERLINE[1];
                else if(c2 == CC_ITALIC[0])
                    result[k] = CC_ITALIC[1];
                else if(c2 == CC_RESET[0])
                    result[k] = CC_RESET[1];
                
                else if(c2 == CC_BLACK[0]) {
                    result[k] = CC_BLACK[1];
                    result[++k] = CC_BLACK[2];
                }
                else if(c2 == CC_DARK_BLUE[0]) {
                    result[k] = CC_DARK_BLUE[1];
                    result[++k] = CC_DARK_BLUE[2];
                }
                else if(c2 == CC_DARK_GREEN[0]) {
                    result[k] = CC_DARK_GREEN[1];
                    result[++k] = CC_DARK_GREEN[2];
                }
                else if(c2 == CC_DARK_AQUA[0]) {
                    result[k] = CC_DARK_AQUA[1];
                    result[++k] = CC_DARK_AQUA[2];
                }
                else if(c2 == CC_DARK_RED[0]) {
                    result[k] = CC_DARK_RED[1];
                    result[++k] = CC_DARK_RED[2];
                }
                else if(c2 == CC_DARK_PURPLE[0]) {
                    result[k] = CC_DARK_PURPLE[1];
                    result[++k] = CC_DARK_PURPLE[2];
                }
                else if(c2 == CC_GOLD[0]) {
                    result[k] = CC_GOLD[1];
                    result[++k] = CC_GOLD[2];
                }
                else if(c2 == CC_GRAY[0]) {
                    result[k] = CC_GRAY[1];
                    result[++k] = CC_GRAY[2];
                }
                else if(c2 == CC_DARK_GRAY[0]) {
                    result[k] = CC_DARK_GRAY[1];
                    result[++k] = CC_DARK_GRAY[2];
                }
                else if(c2 == CC_BLUE[0]) {
                    result[k] = CC_BLUE[1];
                    result[++k] = CC_BLUE[2];
                }
                else if(c2 == CC_GREEN[0]) {
                    result[k] = CC_GREEN[1];
                    result[++k] = CC_GREEN[2];
                }
                else if(c2 == CC_AQUA[0]) {
                    result[k] = CC_AQUA[1];
                    result[++k] = CC_AQUA[2];
                }
                else if(c2 == CC_RED[0]) {
                    result[k] = CC_RED[1];
                    result[++k] = CC_RED[2];
                }
                else if(c2 == CC_LIGHT_PURPLE[0]) {
                    result[k] = CC_LIGHT_PURPLE[1];
                    result[++k] = CC_LIGHT_PURPLE[2];
                }
                else if(c2 == CC_YELLOW[0]) {
                    result[k] = CC_YELLOW[1];
                    result[++k] = CC_YELLOW[2];
                }
                else if(c2 == CC_WHITE[0]) {
                    result[k] = CC_WHITE[1];
                    result[++k] = CC_WHITE[2];
                }

                k++;
            }

            // 

            for(int j = 0; j < ESCAPE_CODE_END_LENGTH; ++j)
                result[k+j] = ESCAPE_CODE_END[j];
            k += ESCAPE_CODE_END_LENGTH;

            // 

            _i = k;
            check_color_case = 0;
        }
        c = str[i];
        result[_i] = c;

        check_color_case = c == COLOR_CASE;
    }
    result[_i-1] = '-';

    // 

    // APPEND RESET ESCAPE CODE AT THE END :

    k = _i-1;

    if(COLOR_DEBUG) {
        for(int j = 0; j < ESCAPE_CODE_START_COLOR_DEBUG_LENGTH; ++j)
            result[k+j] = ESCAPE_CODE_START_COLOR_DEBUG[j];
        k += ESCAPE_CODE_START_COLOR_DEBUG_LENGTH;
    }
    else {
        for(int j = 0; j < ESCAPE_CODE_START_LENGTH; ++j)
            result[k+j] = ESCAPE_CODE_START[j];
        k += ESCAPE_CODE_START_LENGTH;
    }

    result[k] = CC_RESET[1];
    k++;

    for(int j = 0; j < ESCAPE_CODE_END_LENGTH; ++j)
        result[k+j] = ESCAPE_CODE_END[j];
    k += ESCAPE_CODE_END_LENGTH;

    // 

    result[result_length] = '\0';

    return result;
}

// 

char* colordebug(char* str) {
    COLOR_DEBUG = 1;
    char* result = color(str);
    COLOR_DEBUG = 0;
    return result;
}

//

char* unescape(char* str) {
    int result_length = 0;

    int in_escape = 0;
    char c;
    for(int i = 0; (c = str[i]) != '\0'; ++i) {
        if(c == '\x1b' && str[i+1] == '[')
            in_escape = 1;

        if(!in_escape)
            result_length++;

        if(c == 'm')
            in_escape = 0;
    }

    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );

    in_escape = 0;
    int k = 0;
    for(int i = 0; (c = str[i]) != '\0'; ++i) {
        if(c == '\x1b' && str[i+1] == '[')
            in_escape = 1;

        if(!in_escape) {
            result[k] = str[i];
            k++;
        }

        if(c == 'm')
            in_escape = 0;
    }
    result[result_length] = '\0';

    return result;
}

// 