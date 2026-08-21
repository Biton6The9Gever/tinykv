#include "utils.h"

char* point_to_start(char* str)
{
    while(*str != '\0' && (isspace(*str) || !isprint(*str)))
    {
        str++;
    }
    return str;
}

char* point_to_space(char* str)
{
    while (*str != '\0' && !isspace(*str))
    {
        str++;
    }
    return str;
}

int is_empty_str(char *str ,char *msg)
{
    if(!*str)
    {
        print_err(msg);
        return 1;
    }
    return 0;
}

void print_err(char *message)
{
    fprintf(stderr,"tinykv> %s \n", message);
}