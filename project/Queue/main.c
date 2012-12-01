#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "queue.h"

typedef struct 
{
	char *str;
	int counter;
} word_t;

word_t * make_word(const char *ret)
{
	word_t *w;

	w = malloc(sizeof(word_t));
	assert(w);
	w->counter = 1; 
	w->str = malloc(strlen(ret) + 1);
	assert(w->str);
	strcpy(w->str, ret);
	return w;
}

bool is_alpha(char ch)
{
	if ((ch >= 'a' && ch <= 'z') ||
		(ch >= 'A' && ch <= 'Z'))
		return true;
	return false;
}

void string_filter(char *str)
{
	int i;

	for (i = 0; str[i]; i ++) {
		if (! is_alpha(str[i])) {
			str[i] = ' ';
		}
	}
}

int com_find(const void *f, const void *s)
{
	const word_t *pf = f;
	const char *ps = s;

	return strcasecmp(pf->str, ps);
}

void parser_a_file(Queue *queue, const char *file)
{
	FILE *fp;
	char *ret, *tmp;
	char buffer[4096];

	fp = fopen(file, "r");
	assert(fp);

	while(fgets(buffer, sizeof(buffer), fp) != NULL) {

		tmp = buffer;
		string_filter(buffer);

		while((ret = strsep(&tmp, " ")) != NULL) {
			if (strlen(ret) > 0) {
				word_t *w;
				if ((w = queue_find(queue, 
									ret, com_find)) != NULL) {
					w->counter ++;
				} else {
					w = make_word(ret);
					queue_enqueue(queue, w);
				}
			}
		}

	}
	fclose(fp);
}

void parser_all_files(Queue *queue, const char *file_list)
{
	FILE *fp;
	char buffer[4096];

	fp = fopen(file_list, "r");
	assert(fp);

	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strlen(buffer) - 1] = 0;
		printf("Paring file: %s\n", buffer);
		parser_a_file(queue, buffer);
	}
	fclose(fp);
}

void show_result(Queue *queue)
{
	while(! queue_is_empty(queue)) {
		word_t *w = queue_dequeue(queue);
		printf("%d: %s\n", w->counter, w->str);
		free(w->str);
		free(w);
	}
}

int com_sort(const void *f, const void *s)
{
	const word_t *pf = f;
	const word_t *ps = s;

	return pf->counter - ps->counter;
}
int main(int argc, char *argv[])
{
	int i;
	Queue queue;

	queue_init(&queue);
	for (i = 1; i < argc; i ++) {
		parser_all_files(&queue, argv[i]); 
	}
	queue_sort(&queue, com_sort);
	show_result(&queue);
	queue_destroy(&queue);
	return 0;
}
