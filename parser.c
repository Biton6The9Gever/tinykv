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
    
    printf("Nate Higgerson");
    return (command_t)SET;
}