#pragma once

// 

#ifndef __LOGGER_H__
#define __LOGGER_H__

// 

#define LOGGER_LOG_PREFIX     "&7[  &eLog&7  ]&r "
#define LOGGER_INFO_PREFIX    "&7[ &9Info&7  ]&r "
#define LOGGER_WARNING_PREFIX "&7[&6Warning&7]&r "
#define LOGGER_ERROR_PREFIX   "&7[ &cError&7 ]&r "
#define LOGGER_DEBUG_PREFIX   "&7[ &3Debug&7 ]&r "

// 

typedef char* (*Logger_Formatter)(char* str);

// 

/*
| /////////////////////////////////////////////////////////////////////////////////////
| /!\ This structure needs to be declared in this header to use its members as methods.
| /////////////////////////////////////////////////////////////////////////////////////
*/
typedef struct logger_struct {
    Logger_Formatter log;
    Logger_Formatter info;
    Logger_Formatter warn;
    Logger_Formatter error;
    Logger_Formatter debug;
} * Logger;

// 

extern Logger GetLogger();

// 

#define logger GetLogger()

// 

#endif