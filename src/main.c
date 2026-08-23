#include <stdio.h>
#include "parser.h"

int lunch()
{
    char input[MAX_INPUT_LEN+1] = {0};
    hashMap *db=mp_init();
    printf("tinykv> ");
    while (fgets(input, sizeof(input), stdin)) {
        if (!parse_command(input, db)) {
            break;
        }
        printf("tinykv> ");
    }
    mp_free(db);
    return 0;
}

int main()
{
    return lunch();
}