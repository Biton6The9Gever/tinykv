#include "utils.h"

char* point_to_start(char* str)
{
    while(*str != '\0' && (isspace(*str) || !isprint(*str)))
    {
        str++;
    }
    return str;
}

