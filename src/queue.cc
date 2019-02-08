#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
// Taken from https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
struct Queue
{
    int front,rear,size;
    unsigned capacity;
    char** array;
};

/* constructor for Queue */
struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue  = (struct Queue*) malloc(sizeof(struct Queue));
	queue->capacity = capacity;
    	queue->front = queue->size = 0; 
    	queue->rear = capacity - 1;  // This is important, see the enqueue
    	queue->array = (char**) malloc(queue->capacity * sizeof(char*));
    	return queue;
}

// Queue is full when size becomes equal to the capacity 
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{  return (queue->size == 0); }

// Function to add an item to the queue.  
// It changes rear and size
void enqueue(struct Queue* queue, char* item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = strdup(item);
    queue->size = queue->size + 1;
}

// Function to remove an item from queue. 
// It changes front and size
char* dequeue(struct Queue* queue)
{
    if (isEmpty(queue)){
	printf("queue empty");
        return NULL;
    }
    char* item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
char* front(struct Queue* queue)
{
    if (isEmpty(queue))
	printf("empty queue");    
        return NULL;
    return queue->array[queue->front];
}
 
// Function to get rear of queue
char* rear(struct Queue* queue)
{
    if (isEmpty(queue))
        printf("empty queue"); 
        return NULL;
    return queue->array[queue->rear];
}
