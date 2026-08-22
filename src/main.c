#include <stdio.h>
#include "parser.h"



int main() {
    char input[MAX_INPUT_LEN];
    hashMap *db=mp_init();
    mp_set(db,"BI","TON");
    mp_print(db);
    while(1)
    {
        printf("tinykv> ");
        fgets(input,(sizeof(input)),stdin);
        parse_command(input,db);
        //mp_print(db);
    }
    // השם ייקח אותי אם אני יודע מה זה C
    free(db);
    return 0;
}