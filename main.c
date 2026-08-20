#include <stdio.h>
#include "parser.h"

int main() {
    char input[100];
    printf("tinykv> ");
    fgets(input,(sizeof(input)),stdin);
    parse_command(input);
    // השם ייקח אותי אם אני יודע מה זה C
    return 0;
}