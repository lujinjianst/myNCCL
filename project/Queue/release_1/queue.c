#include <stdbool.h>

#define MAX 32
int arr[MAX];
int head;
int tail;

void queue_init(void)
{
	head = tail = 0;
}
void queue_destroy(void)
{
	head = tail = 0;
}
void queue_enqueue(int value)
{
	arr[tail ++] = value;
}
int queue_dequeue(void)
{
	return arr[head ++];
}

bool queue_is_empty(void)
{
	return head == tail;
}
bool queue_is_full(void)
{
	return tail == MAX;
}



