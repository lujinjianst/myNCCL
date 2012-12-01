#include <stdlib.h>
#include <assert.h>

#include "queue.h"

void queue_init(Queue *queue)
{
	queue->head = NULL;
	queue->tail = NULL;
}
void queue_destroy(Queue *queue)
{
}
static inline struct node *make_node(void *data)
{
	struct node *n;

	n = malloc(sizeof(struct node));
	assert(n);
	n->data = data;
	n->next = NULL;
	return n;
}

static void _queue_enqueue(Queue *queue, struct node *n)
{
	if (queue->head == NULL) {
		queue->head = n;
		queue->tail = n;
	} else {
		queue->tail->next = n;
		queue->tail = n;
	}
}
void queue_enqueue(Queue *queue, void *data)
{
	struct node *n;

	n = make_node(data);

	if (queue->head == NULL) {
		queue->head = n;
		queue->tail = n;
	} else {
		queue->tail->next = n;
		queue->tail = n;
	}
}

void *queue_dequeue(Queue *queue)
{
	void *data;
	struct node *n;

	n = queue->head;
	data = n->data;
	queue->head = n->next;
	free(n);
	return data;
}

bool queue_is_empty(Queue *queue)
{
	return queue->head == NULL;
}
bool queue_is_full(Queue *queue)
{
	return false;
}

void * queue_find(Queue *queue, void *data, 
						 compare com)
{
	struct node *n = queue->head;

	while(n != NULL) {
		if (com(n->data, data) == 0) {
			return n->data;
		}
		n = n->next;
	}
	return NULL;
}
static struct node * _find_max_node(Queue *queue, 
					compare com)
{
	struct node *max, *n;

	max = queue->head;
	n = queue->head;

	while(n != NULL) {
		if (com(max->data, n->data) < 0) {
			max = n;
		}
		n = n->next;
	}
	return max;
}

static void _queue_delete(Queue *queue, struct node *n)
{
	struct node *t;

	t = queue->head;

	if (t == n) {
		queue->head = t->next;
		return;
	}

	while(t->next != NULL) {
		if (t->next == n) {
			if (t->next == queue->tail) {
				t->next = t->next->next;
				queue->tail = t;
				return;
			}
			t->next = t->next->next;
			return;
		}
		t = t->next;
	}

}
void queue_sort(Queue *queue, compare com)
{
	Queue q;
	struct node *n;

	queue_init(&q);

	while(! queue_is_empty(queue)) {
		n = _find_max_node(queue, com);
		_queue_delete(queue, n);
		_queue_enqueue(&q, n);
	}
	queue->head = q.head;
	queue->tail = q.tail;
}
