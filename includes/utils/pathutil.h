#pragma once

// 

#ifndef __PATH_UTIL_H__
#define __PATH_UTIL_H__

// 

/*
|
| name: pathResolve
|
| description:
|   Resolves a given relative path (example : pathResolve("./test/a/../b/x.txt") -> "./test/b/x.txt"
|
| arguments:
|   - <p: char*> - path to resolve
|
| return <: char*>
|
*/
extern char* pathResolve(char* p);

// 

/*
|
| name: pathDirname
|
| description:
|   Gives the parent directory path of another path (example : pathDirname("./test/a/x.txt") -> "./test/a/", or pathDirname("./test/a/") -> "./test/")
|
| arguments:
|   - <p: char*> - path from which getting the parent directory path
|
| return <: char*>
|
*/
extern char* pathDirname(char* p);

// 

/*
|
| name: pathJoin
|
| description:
|   Concat properly two given paths in one (not resolved) path (example : pathJoin("./test/a", "x.txt") -> "./test/a/x.txt").
|
| arguments:
|   - <p1: char*> - first path to concat
|   - <p2: char*> - second path to concat
|
| return <: char*>
|
*/
extern char* pathJoin(char* p1, char* p2);

// 

#endif