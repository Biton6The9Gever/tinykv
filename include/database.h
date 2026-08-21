#ifndef DATABASE_H
#define DATABASE_H
#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct db_node {
    char key[MAX_KEY_LEN];
    char val[MAX_VAL_LEN];
    struct db_node *next;
} db_node;

typedef struct {
    db_node *buckets[1];
    size_t total_entries;
} Database;

int db_init(Database *db);


int db_add_item(Database *db, char *key, char *val);

#endif