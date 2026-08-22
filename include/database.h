#ifndef DATABASE_H
#define DATABASE_H
#include "const.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    char *val;
    struct node *next;
} node;

typedef struct {
    node **buckets;
    size_t capacity;
    size_t total_entries;
} hashMap;

hashMap* mp_init();

void setNode(node* node,char *key, char *val);

int mp_add_item(hashMap *mp, char *key, char *val);

void mp_free(hashMap *mp);

void mp_resize(hashMap *mp, size_t new_capacity);

int mp_set(hashMap *mp, char *key, char *val);

char *mp_get(hashMap *mp,char *key);

int save_database(hashMap *mp, char* file_name);

unsigned long hash_func(const char *str);

void mp_print(hashMap *mp);
#endif