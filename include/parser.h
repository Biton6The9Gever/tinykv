#ifndef PARSER_H
#define PARSER_H
#include "utils.h"
#include "const.h"
#include "database.h"
#include <stdio.h>
#include <string.h>

typedef enum 
{
    SET_CMD,
    GET_CMD,
    DELETE_CMD,
    QUIT_CMD,
    INVALID_CMD
}Command_t;

// Main function which parse the input
void parse_command(char *input , Database *db);
// Extract the command from the input
Command_t get_command(char *input);
// Apply the SET command
void parse_set(char *input , Database *db);

#endif // PARSER_H