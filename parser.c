#include "parser.h"

void parse_command(char *input)
{
    char workInput[MAX_INPUT_LEN];
    command_t t;
    strncpy(workInput,input,strlen(input));

    //remove unnecessary whitespaces in the begging of the cmd
    point_to_start(workInput);
    t = get_command(workInput);
    printf("%d",t);
}
command_t get_command(char *input)
{   
    char cmd[MAX_CMD_LEN + 1];
    sscanf(input, RESOLVE(MAX_CMD_LEN), cmd);
    if (strcmp(cmd, "SET") == 0)
        return SET_CMD;
    else if (strcmp(cmd, "GET") == 0)
        return GET_CMD;
    else if (strcmp(cmd, "DELETE") == 0)
        return DELETE_CMD;
    else if (strcmp(cmd, "QUIT") == 0)
        return QUIT_CMD;
    return INVALID_CMD;
}