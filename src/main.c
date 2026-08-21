#include <stdio.h>
#include "parser.h"



int main() {
    char input[MAX_INPUT_LEN];
    hashMap *db=mp_init();
    if (!db) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }
    printf("tinykv> ");
    fgets(input,(sizeof(input)),stdin);
    parse_command(input,db);
    mp_print(db);
    // השם ייקח אותי אם אני יודע מה זה C
    return 0;
}