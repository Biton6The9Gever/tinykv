#include <stdio.h>

int main() {
    char database[100];
    printf("tinykv> ");
    fgets(database,(sizeof(database)),stdin);
    printf("\n %s",database);
    // השם ייקח אותי אם אני יודע מה זה C
    return 0;
}