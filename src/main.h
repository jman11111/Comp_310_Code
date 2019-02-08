#include <stdio.h>

/*main methods to abstract code, makes it look cleaner*/

void hashtab_insert(HashTable_t *hashtab, char *word, Queue *queue);

static int compreg (regex_t * r, const char * regex_text);

void del_from_hashtab(HashTable_t *hashtab, Queue *queue);

