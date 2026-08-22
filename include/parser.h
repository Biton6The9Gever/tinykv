#ifndef PARSER_H
#define PARSER_H
#include "utils.h"
#include "const.h"
#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum 
{
    SET_CMD,
    GET_CMD,
    DELETE_CMD,
    QUIT_CMD,
    INVALID_CMD
}command_t;

// main function which parse the input
bool parse_command(char *input , hashMap *db);
// extract the command from the input
command_t get_command(char *input);
// apply the SET command
bool parse_set(char *input , hashMap *db);
// apply the QUIT command
bool quit();

bool parse_get(char *input,hashMap *db);

#endif // PARSER_H