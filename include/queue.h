#include <stdio.h>

struct Queue
{
    int front, rear, size;
    unsigned capacity;
    char** array;
};

/* Queue functions */
struct Queue* createQueue(unsigned capacity);

extern int isFull(struct Queue* queue);

extern int isEmpty(struct Queue* queue);

extern void enqueue(struct Queue* queue, char* item);

extern char* dequeue(struct Queue* queue);

extern char* front(struct Queue* queue);

extern char* rear(struct Queue* queue);

