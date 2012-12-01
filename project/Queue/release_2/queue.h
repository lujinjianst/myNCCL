#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAX	5

typedef struct 
{
	int arr[MAX];
	int head;
	int tail;
	int counter;
} Queue;

#include <stdbool.h>

extern void queue_init(Queue *queue);
extern void queue_destroy(Queue *queue);
extern void queue_enqueue(Queue *queue, int value);
extern int queue_dequeue(Queue *queue);
extern bool queue_is_empty(Queue *queue);
extern bool queue_is_full(Queue *queue);

#endif	//_QUEUE_H_
