#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h" 

/*code taken from https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/ */

node createNode()
{
	node temp;
	temp = (node)malloc(sizeof(struct link_list));
	temp ->next = NULL;
	return temp;
}

void printlist(node head)
{
	node tempy = head;
        while(tempy != NULL)
	{
		printf ("'%s': '%i' times\n",tempy->word,tempy->counter);
        	tempy = tempy->next;
        }
}

void delete_end(node head)
{
	node tempy = head;
	node new_last;
        while(tempy->next != NULL)
        {
		new_last = tempy;
        	tempy = tempy->next;
        }
	free(new_last->next);
	new_last->next = NULL;
}

/*adds node at end and all others are shifted down*/
node addNode(node head,char* str,int count)
{
	node temp,tempy;
	temp = createNode();
	temp ->word = strdup(str);
        temp ->counter = count;
	if(head == NULL)
	{
		head = temp;
	}	
	else{
		tempy = head;
		while(tempy->next != NULL){
			tempy = tempy->next;
		}
		tempy-> next = temp;
	}
	return head;
}


/* Given a reference (pointer to pointer) to the head of a list
   and an int,  inserts a new node on the front of the list. */
void push(node* head, char* str,int count)
{
    /* 1. allocate node */
    node new_node = (node) malloc(sizeof(struct link_list));

    /* 2. put in the data  */
    new_node->word  = strdup(str);
    new_node->counter  = count;

    /* 3. Make next of new node as head */
    new_node->next = (*head);

    /* 4. move the head to point to the new node */
    (*head) = new_node;
}


/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAfter(node prev_node,char* str,int count)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
       printf("the given previous node cannot be NULL");
       return;
    }

    /* 2. allocate new node */
    node new_node =(node) malloc(sizeof(struct link_list));

    /* 3. put in the data  */
    new_node->word  = strdup(str);
    new_node->counter  = count;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}

