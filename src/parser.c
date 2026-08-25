#include "parser.h"

bool parse_command(char *input , hashMap *db)
{

    //remove unnecessary whitespaces in the begging of the cmd
    input = point_to_start(input);
    command_t cmd = get_command(input);
    switch (cmd)
    {
        case SET_CMD:
            return parse_set(input,db);
            break;
        case GET_CMD:
            return parse_get(input,db);
            break;
        case QUIT_CMD:
            return quit(db);
            break;
        case DELETE_CMD:
            return parse_delete(input,db);
            break;
        case EMPTY_CMD:
            return true;
            break;
        default:
            print_err("unknown command");
            return true;
            break;
    }
}

command_t get_command(char *input)
{   
    char cmd[MAX_CMD_LEN + 1];
    if(sscanf(input, RESOLVE(MAX_CMD_LEN), cmd)!=1){
        return EMPTY_CMD;
    }

    if (strcmp(cmd, "SET") == 0) return SET_CMD;
    if (strcmp(cmd, "GET") == 0) return GET_CMD;
    if (strcmp(cmd, "DELETE") == 0) return DELETE_CMD;
    if (strcmp(cmd, "QUIT") == 0) return QUIT_CMD;

    return INVALID_CMD;
}

bool parse_set(char *input, hashMap *db)
{
    char *ptr = input;

    char *key = get_arg(&ptr);
    if (!key) return true;

    char *val = get_arg(&ptr);
    if (!val) {
        free(key);
        return true;
    }

    if(!mp_set(db, key, val))
    {
        free(key);
        free(val);
        return quit(db);
    }

    free(key);
    free(val);
    return true;
}

bool parse_get(char *input, hashMap *db)
{
    char *ptr = input;

    char *key = get_arg(&ptr);
    if (!key) return true;

    char *val = mp_get(db, key);
    if (!val) {
        print_err("no value for this key");
        free(key);
        return true;
    }

    printf("val: \"%s\"\n", val);
    free(key);
    return true;
}

bool quit(hashMap *db)
{
    save_database(db,"database"); 
    return false;
}

bool parse_delete(char *input, hashMap *db)
{
    char *ptr = input;

    char *key = get_arg(&ptr);
    if (!key) return true;

    if (!mp_delete(db, key))
    {
        print_err("key not found");
    }
    else 
    {
        print_msg("Key and Val deleted succesfully");
    }

    free(key);
    return true;
}

char* get_arg(char **input_ptr)
{
    if (!input_ptr || !*input_ptr) return NULL;

    char *ptr = point_to_space(*input_ptr);
    ptr = point_to_start(ptr);

    if (is_empty_str(ptr, "not enough arguments were given")) {
        *input_ptr = ptr;
        return NULL;
    }

    char *arg_start = ptr;
    ptr = point_to_space(ptr);
    size_t arg_len = ptr - arg_start;

    char *arg = strndup(arg_start, arg_len);
    if (!arg) {
        print_err("allocation failed");
        return NULL;
    }

    // update the pointer to the end of the argument
    *input_ptr = ptr;
    return arg;
}


