#include "../../includes/utils/logger.h"

// 

#include <stdio.h>
#include <stdbool.h>

// 

#include "../../includes/utils/tempalloc.h"
#include "../../includes/utils/color.h"

// 

static char* formatlog(char* prefix, char* str) {
    char* c_prefix = color(prefix);

    int str_length;
    for(str_length = 0; str[str_length] != '\0'; ++str_length);
    bool caret_return = str[str_length-1] != '\1';

    char* c_str = color(str);

    int c_prefix_length;
    for(c_prefix_length = 0; c_prefix[c_prefix_length] != '\0'; ++c_prefix_length);

    int c_str_length;
    for(c_str_length = 0; c_str[c_str_length] != '\0'; ++c_str_length);

    int result_length = c_prefix_length+c_str_length+(caret_return ? 1 : 0);
    char* result = tempalloc->allocate( sizeof(char) * (result_length+1) );

    int i;
    for(i = 0; i < c_prefix_length; ++i)
        result[i] = c_prefix[i];
    for(int j = 0; j < c_str_length; ++j, ++i)
        result[i] = c_str[j];
    
    if(caret_return)
        result[result_length-1] = '\n';

    result[result_length] = '\0';

    return result;
}

// 

static char* logger_log_func(char* str) {
    return formatlog((char*) LOGGER_LOG_PREFIX, str);
}

static char* logger_info_func(char* str) {
    return formatlog((char*) LOGGER_INFO_PREFIX, str);
}

static char* logger_warn_func(char* str) {
    return formatlog((char*) LOGGER_WARNING_PREFIX, str);
}

static char* logger_error_func(char* str) {
    return formatlog((char*) LOGGER_ERROR_PREFIX, str);
}

static char* logger_debug_func(char* str) {
    return formatlog((char*) LOGGER_DEBUG_PREFIX, str);
}

// 

static Logger _logger = NULL;

Logger GetLogger() {
    _logger = _logger == NULL ? tempalloc->allocate( sizeof(struct logger_struct) * 1 ) : _logger;

    _logger->log = logger_log_func;
    _logger->info = logger_info_func;
    _logger->warn = logger_warn_func;
    _logger->error = logger_error_func;
    _logger->debug = logger_debug_func;

    return _logger;
}

// 

#define logger GetLogger()

// 