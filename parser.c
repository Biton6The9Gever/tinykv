#include "parser.h"

void parse_command(char *input)
{
    char workInput[sizeof(input)+1];
    strncpy(workInput,input,strlen(input));

    //remove unnecessary whitespaces in the begging of the cmd
    point_to_start(workInput);
    get_command(workInput);
}
command_t get_command(char *input)
{
    char cmd[6];
    sscanf(input,"%6s",cmd);
    printf("COMMAND: %s \n",cmd);
    return (command_t)SET;
}