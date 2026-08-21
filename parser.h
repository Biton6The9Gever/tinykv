#ifndef PARSER_H
#define PARSER_H
#include "utils.h"
#include "const.h"
#include <stdio.h>
#include <string.h>


typedef enum 
{
    SET_CMD,
    GET_CMD,
    DELETE_CMD,
    QUIT_CMD,
    INVALID_CMD
}command_t;

void parse_command(char *input);
command_t get_command(char *input);

#endif // PARSER_H