#include <stdio.h>
#include "parser.h"



int main() {
    char input[MAX_INPUT_LEN];
    hashMap *db=mp_init();
    
    while (fgets(input, sizeof(input), stdin)) {
        if (!parse_command(input, db)) {
            break;
        }
    }
    
    mp_free(db);
    return 0;
}