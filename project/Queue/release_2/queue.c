#include "queue.h"

void queue_init(Queue *queue)
{
	queue->tail = 0;
	queue->head = 0;
	queue->counter = 0;
}
void queue_destroy(Queue *queue)
{
	queue->tail = 0;
	queue->head = 0;
	queue->counter = 0;
}
void queue_enqueue(Queue *queue, int value)
{
	queue->counter ++;
	queue->arr[queue->tail ++] = value;
	queue->tail %= MAX;
}
int queue_dequeue(Queue *queue)
{
	int value;
	queue->counter --; 
	value = queue->arr[queue->head ++];
	queue->head %= MAX;
	return value;
}
bool queue_is_empty(Queue *queue)
{
	return queue->counter == 0;
}
bool queue_is_full(Queue *queue)
{
	return queue->counter == MAX;
}


