#include "parser.h"

void parse_command(char *input , Database *db)
{
    if(!db) return; //problemo el code
    char workInput[MAX_INPUT_LEN];
    strncpy(workInput,input,strlen(input));

    //remove unnecessary whitespaces in the begging of the cmd
    point_to_start(workInput);
    parse_set(input,db);
}

Command_t get_command(char *input)
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

void parse_set(char *input , Database *db)
{
    char key[MAX_KEY_LEN+1];
    char val[MAX_VAL_LEN+1];
    
    char *ptr = input;

    ptr=point_to_space(ptr);
    ptr=point_to_start(ptr);

    sscanf(ptr, RESOLVE(MAX_KEY_LEN), key);

    ptr=point_to_space(ptr);
    ptr=point_to_start(ptr);

    sscanf(ptr, RESOLVE(MAX_VAL_LEN), val);
    printf("key: %s    val: %s \n",key ,val);
    db_add_item(db,key,val);
}