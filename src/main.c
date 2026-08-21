#include <stdio.h>
#include "parser.h"



int main() {
    char input[MAX_INPUT_LEN];
    Database db;
    db_init(&db);
    printf("tinykv> ");
    fgets(input,(sizeof(input)),stdin);
    parse_command(input,&db);
    // השם ייקח אותי אם אני יודע מה זה C
    return 0;
}