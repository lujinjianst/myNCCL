#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#include "queue.h"

int main(int argc, char *argv[])
{
	char ch;
	queue_init();
	while((ch = getchar()) != '\n') {
		if (! queue_is_full()) {
			queue_enqueue(ch);
		}
	}

	while(! queue_is_empty()) {
		putchar(queue_dequeue());
	}
	queue_destroy();
	return 0;
}

