#ifndef PARSER_H
#define PARSER_H
#include "utils.h"
#include <stdio.h>
#include <string.h>

typedef enum 
{
    SET,
    GET,
    DELETE,
    QUIT
}command_t;

void parse_command(char *input);
command_t get_command(char *input)

#endif // PARSER_H