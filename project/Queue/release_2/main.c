#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#include "queue.h"

int main(int argc, char *argv[])
{
	char ch;
	Queue q;
	queue_init(&q);
	while((ch = getchar()) != '\n') {
		if (! queue_is_full(&q)) {
			queue_enqueue(&q, ch);
		}
	}

	while(! queue_is_empty(&q)) {
		putchar(queue_dequeue(&q));
	}
	putchar('\n');
	while((ch = getchar()) != '\n') {
		if (! queue_is_full(&q)) {
			queue_enqueue(&q, ch);
		}
	}
	while(! queue_is_empty(&q)) {
		putchar(queue_dequeue(&q));
	}
	putchar('\n');
	queue_destroy(&q);
	return 0;
}

