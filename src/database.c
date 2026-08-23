#include "database.h"

hashMap* mp_init()
{
    hashMap *mp = malloc(sizeof(hashMap));
    if(!mp) return NULL;
    mp->capacity = INITIAL_CAPACITY;
    mp->total_entries =0;
    mp->buckets= calloc(mp->capacity,sizeof(node*));
    if (!mp->buckets) {
        free(mp);
        return NULL;
    }
    return mp;
}

void setNode(node* node,char *key, char *val)
{
    node->key = strdup(key);
    node->val = strdup(val);
    node->next = NULL;
    return;
}

int mp_add_item(hashMap *mp, char *key, char *val)
{
    if(!mp) return 0;

    // intializing the item node
    node *item= (node *)malloc(sizeof(node));
    if(!item) return 0;

    setNode(item,key,val);

    //adding the node to the mp
    item->next = mp->buckets[0];
    mp->buckets[0] = item;
    mp->total_entries++;

    return 1;
}

//void mp_resize(hashMap *mp, size_t new_capacity) {/*todo*/}

int mp_set(hashMap *mp, char *key, char *val)
{
    size_t idx = hash_func(key) % mp->capacity;
    node *curr = mp->buckets[idx];

    // if key exist update val 
    while(curr)
    {
        if(strcmp(curr->key,key) == 0)
        {
            free(curr->val);
            curr->val = strdup(val);
            return 1;
        }
        curr = curr->next;
    }

    node *new_node =malloc(sizeof(node));
    if(!new_node) return 0;
    new_node->key =strdup(key);
    new_node->val =strdup(val);
    new_node->next = mp->buckets[idx];
    mp->buckets[idx] = new_node;
    mp->total_entries++;

    return 1;
}

void mp_free(hashMap *mp)
{
    if(!mp) return;

    for(size_t i=0; i<mp->capacity;i++)
    {
        node *curr = mp->buckets[i];
        while(curr)
        {
            node *temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp->val);
            free(temp);
        }
    }
    free(mp->buckets);
    free(mp);
}

void mp_print(hashMap *mp,FILE *output_stream)
{
    if(!mp) return;

    for(size_t i=0; i<mp->capacity;i++)
    {
        node *curr = mp->buckets[i];
        if(curr)
        {
            fprintf(output_stream,"[ %zu ]", i);
            while(curr)
            {
                fprintf(output_stream, " -> [key: \"%s\"], [val: \"%s\"]", curr->key, curr->val);
                curr = curr->next;
            }
           fprintf(output_stream," -> NULL\n");
        }
    }
}

char *mp_get(hashMap *mp,char *key) {
    size_t idx = hash_func(key) % mp->capacity;
    node *curr = mp->buckets[idx];

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

int save_database(hashMap *mp, char* name)
{
    // +4 for .txt and +1 for \0
    size_t required_size = strlen(name) + 5;
    
    char *file_name = malloc(required_size);
    if (file_name == NULL) {
        print_err("memory allocation failed");
        return 0; 
    }
    
    snprintf(file_name, required_size, "%s.txt", name);
    
    FILE *mp_file = fopen(file_name, "w");
    if (mp_file == NULL) {
        fprintf(stderr,"tinykv> error could not create file %s\n", file_name);
        free(file_name);
        return 0; 
    }
    
    mp_print(mp, mp_file);
    fclose(mp_file);

    printf("tinykv> database saved into %s \n", file_name);
    free(file_name);
    
    return 1;
}

unsigned long hash_func(const char *str)
{
    unsigned long hash = 5381;
    const unsigned char *s = (const unsigned char *)str;
    int c;

    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}


