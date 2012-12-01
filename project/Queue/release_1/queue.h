#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

extern void queue_init(void);
extern void queue_destroy(void);
extern void queue_enqueue(int value);
extern int queue_dequeue(void);
extern bool queue_is_empty(void);
extern bool queue_is_full(void);

#endif	//_QUEUE_H_
