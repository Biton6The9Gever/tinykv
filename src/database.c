#include "database.h"

hashMap* mp_init(void)
{
    hashMap *mp = malloc(sizeof(hashMap));
    if(!mp) return NULL;
    
    mp->capacity = INITIAL_CAPACITY;
    mp->total_entries =0;
    mp->buckets= calloc(mp->capacity,sizeof(node*));

    if (!mp->buckets)
    {
        free(mp);
        return NULL;
    }
    return mp;
}

bool set_node(node* node,char *key, char *val)
{
    node->key = strdup(key);
    node->val = strdup(val);
    if(!node->key || !node->val)
    {
        free(node->key);
        free(node->val);
        return false;
    }
    node->next = NULL;
    return true;
}


void mp_resize(hashMap *mp, size_t new_capacity)
{
    if (!mp) return;

    node **new_buckets = calloc(new_capacity,sizeof(node*));
    if(!new_buckets) return;
    for(size_t i =0 ; i < mp->capacity; i++)
    {
        node *curr = mp->buckets[i];
        while(curr)
        {
            node *next = curr->next;
            
            //re-hashing
            size_t new_idx =hash_func(curr->key) % new_capacity;
            curr->next = new_buckets[new_idx];
            new_buckets[new_idx]=curr;

            curr=next;
        }
    }
    free(mp->buckets);
    mp->buckets = new_buckets;
    mp->capacity = new_capacity;
}

bool mp_set(hashMap *mp, char *key, char *val)
{
    if (!mp || !key || mp->capacity == 0) return false;

    if ((double)(mp->total_entries + 1) / (double)mp->capacity > FACTOR_THRESHOLD)
    {
        mp_resize(mp, mp->capacity * 2);
    }
    size_t idx = hash_func(key) % mp->capacity;
    node *curr = mp->buckets[idx];

    // if key exist update val 
    while(curr)
    {
        if(strcmp(curr->key,key) == 0)
        {
            char *new_value = strdup(val);
                if (!new_value)
                {
                    return 0;
                }

            free(curr->val);
            curr->val = new_value;
            return true;
        }
        curr = curr->next;
    }

    node *new_node =malloc(sizeof(node));
    if(!new_node) return false;

    if (!set_node(new_node, key, val))
    {
        free(new_node);
        return false;
    }

    new_node->next = mp->buckets[idx];
    mp->buckets[idx] = new_node;
    mp->total_entries++;

    return true;
}

bool mp_delete(hashMap *mp, char *key)
{
    if (!mp || !key || mp->capacity == 0) return false;

    size_t idx = hash_func(key) % mp->capacity;
    node *curr = mp->buckets[idx];
    node *prev = NULL;

    while (curr) 
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev == NULL)
            {
                mp->buckets[idx] = curr->next;
            } 
            else
            {
                prev->next = curr->next;
            }

            free(curr->key);
            free(curr->val);
            free(curr);

            if (mp->total_entries > 0) mp->total_entries--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false; 
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
    if (!mp || mp->capacity == 0) return;

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
    if (!mp || !key || mp->capacity == 0) return NULL;

    size_t idx = hash_func(key) % mp->capacity;
    node *curr = mp->buckets[idx];

    while (curr)
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

int save_database(hashMap *mp, char* name)
{
    if (!mp || !name || mp->capacity == 0) return false;
    
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


