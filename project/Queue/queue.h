#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct node
{ 
	void *data;
	struct node *next;
} node;

typedef struct
{
	struct node *head;
	struct node *tail;
} Queue;

typedef int (*compare)(const void *, const void *);
extern void queue_init(Queue *queue);
extern void queue_destroy(Queue *queue);
extern void queue_enqueue(Queue *queue, void *data);
extern void *queue_dequeue(Queue *queue);
extern bool queue_is_empty(Queue *queue);
extern bool queue_is_full(Queue *queue);
extern void * queue_find(Queue *queue, void *data, 
						 compare com);
extern void queue_sort(Queue *queue, compare com);
#endif	//_QUEUE_H_
