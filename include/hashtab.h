/*header for string hashtable */

/* a hash-table implementation in c */
/*
hashing algorithm: hashval = *s + 31 * hashval
resolves collisions using linked lists
*/

#ifndef HASH
#define HASH

typedef struct TableEntry /* hashtab entry */
{
    struct TableEntry *next;
    char *key;
    int val;
} TableEntry_t;

typedef struct HashTable
{
    size_t size;
    int elem;
    struct TableEntry **tab;
} HashTable_t;

/* inserts the key-val pair */
TableEntry_t *ht_insert(HashTable_t *ht, char *k, int v);

/* creates hashtable */
/* NOTE: dynamically allocated, remember to ht_free() */
HashTable_t *ht_create(size_t size);

void print_ht(int howmany, HashTable_t *ht);
int compare(const void *elem1, const void *elem2);

void te_free(TableEntry_t*);

/* frees hashtable created from ht_create() */
void ht_free(HashTable_t *ht);

/* retrive value from key */
int ht_index(HashTable_t *ht, char *k);

/* resizes hashtable, returns new hashtable and frees old*/
HashTable_t *ht_resize(HashTable_t *oht, size_t size);

/* Looks up if target key exists */
TableEntry_t *lookup(HashTable_t *ht, char *k);

#endif

