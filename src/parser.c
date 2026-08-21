#include "parser.h"

void parse_command(char *input , hashMap *db)
{
    if(!db) return; //problemo el code

    //remove unnecessary whitespaces in the begging of the cmd
    input=point_to_start(input);
    command_t cmd=get_command(input);
    switch (cmd)
    {
        case SET_CMD:
            parse_set(input,db);
            break;
        case QUIT_CMD:
            break;
        default:
            print_err("unknown command");
            break;
    }
}

command_t get_command(char *input)
{   
    char cmd[MAX_CMD_LEN + 1];
    sscanf(input, RESOLVE(MAX_CMD_LEN), cmd);

    if (strcmp(cmd, "SET") == 0) return SET_CMD;
    if (strcmp(cmd, "GET") == 0) return GET_CMD;
    if (strcmp(cmd, "DELETE") == 0) return DELETE_CMD;
    if (strcmp(cmd, "QUIT") == 0) return QUIT_CMD;

    return INVALID_CMD;
}

void parse_set(char *input , hashMap *db)
{ 
    printf("################");
    char *ptr = input;

    ptr = point_to_space(ptr);
    ptr=point_to_start(ptr);

    if(is_empty_str(ptr,"not enough arguments were given")) return;

    //find end of key
    char *key_start=ptr;
    ptr=point_to_space(ptr);
    size_t key_len=ptr-key_start;

    // find end of val
    ptr=point_to_start(ptr);

    if(is_empty_str(ptr,"not enough arguments were given")) return;

    char *val_start =ptr;
    ptr= point_to_space(ptr);
    size_t val_len= ptr -val_start;

    char *key = strndup(key_start, key_len);
    char *val = strndup(val_start, val_len);

    if (!key || !val) {
        free(key);
        free(val);
        return;
    }

    mp_set(db, key, val);

    free(key);
    free(val);
}

