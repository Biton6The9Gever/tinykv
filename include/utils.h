#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FORMAT(S) "%" #S "s"
#define RESOLVE(S) FORMAT(S)


char* point_to_start(char* str);
// point to the first space of a string
char* point_to_space(char* str);

void print_err(char *message);

int is_empty_str(char *str ,char *msg);
#endif // UTILS_H