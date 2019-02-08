#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtab.h"

/* Taken from https://codereview.stackexchange.com/questions/176023/hash-table-implementation-in-c */
/* creates hashtable */
/* NOTE: dynamically allocated, remember to ht_free() */
HashTable_t *ht_create(size_t size)
{
    HashTable_t *ht = NULL;
    if ((ht = (HashTable_t *)malloc(sizeof(HashTable_t))) == NULL)
        return NULL;
    /* allocate ht's table */
    if ((ht->tab = (TableEntry_t **)malloc(sizeof(TableEntry_t) * size)) == NULL)
        return NULL;
    /* null-initialize table */
    int i;
    for (i = 0; i < size; i++)
        ht->tab[i] = NULL;
    ht->size = size;
    return ht;
}

/* creates hash for a hashtab */
unsigned hash(HashTable_t *ht, char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % ht->size;
}

/* creates a key-val pair */
TableEntry_t *createtab(char *k, int v)
{
    TableEntry_t *te = NULL;
    if ((te = (TableEntry_t *)malloc(sizeof(TableEntry_t))) == NULL)
        return NULL;
    if ((te->key = strdup(k)) == NULL)
        return NULL;
    if ((te->val = v) == 0)
        return NULL;
    te->next = NULL;
    return te;
}

TableEntry_t *lookup(HashTable_t *ht, char *k)
{
    TableEntry_t *te;
    /* step through linked list */
    for (te = ht->tab[hash(ht, k)]; te != NULL; te = te->next)
        if (strcmp(te->key, k) == 0)
            return te; /* found */
    return NULL; /* not found */
}

int ht_delete(HashTable_t *ht, char *k)
{
    if(ht->tab[hash(ht, k)] == NULL) { return 0; }
    /*check if head node is delete target*/
    TableEntry_t *te, *prev;
    te = ht->tab[hash(ht, k)];
    if (strcmp(te->key, k) == 0 && te != NULL)
    	{
            ht->tab[hash(ht, k)] = te->next;
	    ht->elem--;
            te_free(te);
	    return 1;
        }
    /*check the rest of the list for delete target*/
    while (te != NULL && strcmp(te->key,k) != 0) 
    	{ 
            prev = te; 
            te = te->next; 
    	} 
    if (te == NULL) return -1;

    prev->next = te->next;
    ht->elem--;
    te_free(te);

    return 2; /* found */

}

/* inserts the key-val pair */
TableEntry_t *ht_insert(HashTable_t *ht, char *k, int v)
{
    TableEntry_t *te;
    /* unique entry */
    if ((te = lookup(ht, k)) == NULL)
    {
        te = createtab(k, v);
        unsigned hashval = hash(ht, k);
        /* insert at beginning of linked list */
        te->next = ht->tab[hashval]; 
        ht->tab[hashval] = te;
	ht->elem++;
    }
    /* replace val of previous entry */
    else
    {
        te->val = 0;
        if ((te->val = v) == 0)
            return NULL;
    }
    
    return te;
}

/* retrive value from key */
int ht_index(HashTable_t *ht, char *k)
{
    TableEntry_t *te;
    if ((te = lookup(ht, k)) == NULL)
        return 0;
    return te->val;
}

int compare(const void *p, const void *q)
{
        int l = (*(TableEntry_t **)p)->val; 
        int r = (*(TableEntry_t **)q)->val;	
        return (r - l); 
}

int print_ht(int howmany,HashTable_t *ht)
{
	if(ht->elem <= howmany){
                return 0;
        }

	int i, j=0;
	TableEntry_t *l = (TableEntry_t *)malloc(sizeof(TableEntry_t *));
	TableEntry_t **vector = (TableEntry_t **)malloc(ht->elem * sizeof(TableEntry_t *));

	for (i=0; i < ht->size; i++)
	{
		for (l=ht->tab[i]; l != NULL; l=l->next)
		{
            		vector[j++] = l;
		}
	}

	size_t n = sizeof(**vector)/sizeof(TableEntry_t *);
        qsort(vector,ht->elem,sizeof(TableEntry_t *),compare);

	for (i=0; i < howmany; i++)
	{
		if(vector[i] != NULL)
		{
		printf("%s,%d times \n",vector[i]->key,vector[i]->val);
		}
	}
	free(vector);
	return 1;
}

/* recursively frees table entriy chains, starting with last one added */
void te_free(TableEntry_t *te)
{
    free(te->key);
    te->val = 0;
    free(te);
}

/* frees hashtable created from ht_create() */
void ht_free(HashTable_t *ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
        if (ht->tab[i] != NULL)
            te_free(ht->tab[i]);
    free(ht);
}

/* resizes hashtable, returns new hashtable and frees old*/
HashTable_t *ht_resize(HashTable_t *oht, size_t size)
{
    HashTable_t *nht; /* new hashtable */
    nht = ht_create(size);
    /* rehash */
    int i;
    TableEntry_t *te;
    /* loop through hashtable */
    for (i = 0; i < oht->size; i++)
        /* loop through linked list */
        for (te = oht->tab[i]; te != NULL; te = te->next)
            if (ht_insert(nht, te->key, te->val) == NULL)
                return NULL;
    ht_free(oht);
    return nht;
}
