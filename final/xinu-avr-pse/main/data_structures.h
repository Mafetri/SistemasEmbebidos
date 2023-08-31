#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#define MAX_SIZE 6

typedef struct queue
{
    unsigned int front;
    unsigned int rear;
    double data[MAX_SIZE][2];
} queue;

void queue_init(queue *q);
int queue_enqueue(queue *q, double value[2]);
int queue_enqueue_values(queue *q, double a, double b);
int queue_dequeue(queue *q, double value[2]);

#endif