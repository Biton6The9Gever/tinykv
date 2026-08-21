#include "database.h"

int db_init(Database *db)
{
    if(!db) return 0;
    db->buckets[0] = NULL;
    db->total_entries = 0;
    return 1; 
}


int db_add_item(Database *db, char *key, char *val)
{
    if(db == NULL) return 0;

    // intializing the item node
    db_node *item= (db_node *)malloc(sizeof(db_node));
    if(!item) return 0;

    strncpy(item->key,key,MAX_KEY_LEN-1);
    (item->key)[MAX_KEY_LEN-1]='\0';

    strncpy(item->val,val,MAX_VAL_LEN-1);
    (item->val)[MAX_VAL_LEN-1]='\0';

    //adding the node to the db
    item->next = db->buckets[0];
    db->buckets[0] = item;
    db->total_entries++;
    
    return 1;
}