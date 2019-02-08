#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <unistd.h>
#include "hashtab.h"
#include "queue.h"
#include <string.h>
#include <getopt.h>

/* all code for getline taken from https://c-for-dummies.com/blog/?p=1112 */
/* code for regex compilation and execution taken from https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples */
/* the way I understand it this code stores the input in the buffer once getline is called, after a char pointer is allocated enough space to hold this getlines input, then the regex checks to see if the line contains words */

void hashtab_insert(HashTable_t *hashtab, char *word, Queue *queue){
	int cur_count;
	/* If the word is not in the hastable, add it with count 1 */
	if(lookup(hashtab,word)==NULL)
        {
    		cur_count = 1;
        }
        /*If the word does exist, increment it by one*/
        else
        {
                cur_count = ht_index(hashtab,word);
                cur_count++;
        }

	ht_insert(hashtab,word,cur_count);
        enqueue(queue,word);

}

void regexmatch(int *c, regex_t r, HashTable_t *hashtab, char *line, Queue *queue, int minlength){
	/* "P" is a pointer into the line which points to the end of the previous match. */
        const char * p = line;
        /* "N_matches" is the maximum number of matches allowed. */
        const int n_matches = 100;
        /* "M" contains the matches found. */
        regmatch_t m[n_matches];
        int matching = 1;
        while (matching) {
        	int start;
                int finish;
                char *matchedword = (char*)malloc((30)*sizeof(char));;
                int nomatch = regexec (&r, p, n_matches, m, 0);
                if (nomatch) {
                	matching = 0;
                }else{
                        start = m[0].rm_so + (p - line);
                        finish = m[0].rm_eo + (p - line);
                        strncpy(matchedword, line+start, (finish-start));
                        if(strlen(matchedword) >= minlength){
                        	hashtab_insert(hashtab,matchedword,queue);
                        	*c = *c + 1;
                	}
                p += m[0].rm_eo;
         	}
        }
}


static int compreg (regex_t * r, const char * regex_text)
{
    	int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
    	if (status != 0) {
		char error_message[100];
		regerror (status, r, error_message, 100);
        	printf ("Regex error compiling '%s': %s\n", regex_text, error_message);
		return 1;
	}
	return 0;
}

void del_from_hashtab(HashTable_t *hashtab, Queue *queue){
	char *deqword;
        int deccount;
	while(isEmpty(queue) == 0){
        	deqword = dequeue(queue);
                deccount = ht_index(hashtab,deqword);
                deccount--;
                if(deccount == 0){
                	ht_delete(hashtab,deqword);
                }else{
                        ht_insert(hashtab,deqword,deccount);
                }
        }

}



int main(int argc, char **argv)
{
    	size_t bufsize = 10000;
    	size_t characters;
    	char linebuf[10000];
	char *line = linebuf;
	int howmany = 10;
        int minlength = 6;
        int lastnwords = 1000;
	int d;
        int c;
	regex_t r;
	char *regex = "(\\w+)";
	struct Queue *queue;
	size_t hashsize = 300;
	HashTable_t *hashtab = ht_create(hashsize);
  	opterr = 0;

  	while (1)
  	{
  	    static struct option long_options[] =
  	      {
  	        /* These options don’t set a flag.
  	           We distinguish them by their indices. */
  	        {"howmany",  required_argument, 0, 'd'},
  	        {"minlength",  required_argument, 0, 'c'},
  	        {"lastnwords",    required_argument, 0, 'f'},
  	        {0, 0, 0, 0}
  	      };
  	    /* getopt_long stores the option index here. */
  	    int option_index = 0;
	
	      d = getopt_long (argc, argv, "c:d:f:",long_options, &option_index);
	
	      /* Detect the end of the options. */
	      if (d == -1)
	        break;
	
	      switch (d)
	        {
	        case 'c':
	          printf ("option minlength with value `%s'\n", optarg);
		  minlength = atoi(optarg);
	          break;
	
	        case 'd':
	          printf ("option howmany with value `%s'\n", optarg);
		  howmany = atoi(optarg);
	          break;
	
	        case 'f':
	          printf ("option lastnwords with value `%s'\n", optarg);
		  lastnwords = atoi(optarg);
	          break;
	
	        case '?':
	          /* getopt_long already printed an error message. */
	          break;
	
	        default:
	          abort ();
	        }
	}
	int eof = 0;
  	queue = createQueue(lastnwords);
	compreg(&r, regex);
	printf("Type something: ");
	while(characters != -1){
		c = 0;
		while(c<lastnwords){
    			characters = getline(&line,&bufsize,stdin) != -1;
			regexmatch(&c,r,hashtab,line,queue,minlength);
	    	}
		print_ht(howmany,hashtab);
		printf("\n");
		del_from_hashtab(hashtab,queue);
	}
	/* Free memory allocated to the pattern buffer by regcomp() */
    	return(0);
}
