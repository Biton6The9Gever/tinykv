#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FORMAT(S) "%" #S "s"
#define RESOLVE(S) FORMAT(S)

char* point_to_start(char* str);

#endif // UTILS_H