#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define NAME_MAX 5
#define NODE_SIZE 5
#define ADD_SIZE 5

typedef struct Word{
	char *name;
	int nu;
	struct Word *next;
}word_t;

static word_t *head_2 = NULL;

static word_t *make_node_2(char *s, word_t *q)
{
	word_t *p = NULL;
	p = q;
	p->name = (char *)malloc(strlen(s) + 1);
	if(p->name == NULL)
	{
		fprintf(stderr, "Usage: malloc in funtion make_node_2 for p->name error: %s!\n", strerror(errno));
		exit(4);
	}
	
	strcpy(p->name, s);

	p->nu = 1;
	p->next = NULL;

	return p;	
}

static int insert_2(char *s, word_t *q)
{
	word_t *p = NULL;
	p = make_node_2(s, q);
	if(p == NULL)
		return -1;

	if(head_2 == NULL)
		head_2 = p;
	else
	{
		p->next = head_2;
		head_2 = p;
	}
		
	return 0;
}

static int destory_2(void)
{
	word_t *p = NULL, *q = NULL;
//	char *s = NULL;

	if(head_2 == NULL)
		return 0;

	else{
		for(p = head_2; p != NULL;)
		{
			q = p->next;
			free(p->name);
			free(p);
			p = q;
		}
	}
	return 0;
}

static word_t *search_2(const char *s_name)
{
	word_t *p = NULL;
	
	for(p = head_2; p != NULL; p = p->next)
	{
		if(strcmp(s_name, p->name) == 0)
			break;
	}

	return p;
}

word_t * count_word_2(FILE *fp)
{
	word_t *word = NULL, *p = NULL;
	int  kev, n;
	char *buf = NULL;
	char *w = NULL;

	kev = 0;
	n = 0;
	word = (word_t *)malloc(sizeof(word_t) * NODE_SIZE);
	if(word == NULL)
	{
		fprintf(stderr, "Usage : malloc for word error: %s!\n", strerror(errno));
		exit(4);
	}

	buf = (char *)malloc(NAME_MAX);
	if(buf == NULL)
	{
		fprintf(stderr, "Usag :malloc for buf error: %s!\n", strerror(errno));
		exit(4);
	}

	while(fgets(buf, NAME_MAX, fp) != NULL)
	{
		int i = 0;
		while(buf[strlen(buf)] == '\0' && buf[strlen(buf) - 1] != '\n')                     //buf's size is litter than that of oneline's, 
		{
			i++;
			buf = realloc(buf, NAME_MAX+ADD_SIZE*i);
			if(buf == NULL)
			{
				fprintf(stderr, "Usage : realloc for buf error: %s!\n", strerror(errno));
				exit(3);
			}
			fgets(buf+strlen(buf), ADD_SIZE+1, fp);
		}
		
		buf[strlen(buf)-1] = '\0';
		
		w = strtok(buf, " ");
		p = search_2(w);
		if(p == NULL)
		{
			if(kev == NODE_SIZE+n*ADD_SIZE)                                                   //not enough size for next node,,realloc
			{
				n++;
				word = realloc(word, NODE_SIZE+n*ADD_SIZE);
				if(word == NULL)
				{
					fprintf(stderr, "Usage: realloc in function count_word_2 for word error: %s!\n", strerror(errno));
					exit(3);
				}
			}
			insert_2(w, word+(kev*(sizeof(word_t))));
			kev++;
		}
		if(p != NULL)
			p->nu++;
		while((w = strtok(NULL, " ")) != NULL)
		{
			p = search_2(w);
			if(p == NULL)
			{
				if(kev == NODE_SIZE+n*ADD_SIZE)
				{
					n++;
					word = realloc(word, NODE_SIZE+n*ADD_SIZE);
					if(word == NULL)
					{
						fprintf(stderr, "Usage: realloc in function count_word_2 for word error: %s!\n", strerror(errno));
						exit(3);
					}
				}
				insert_2(w, word+(kev*(sizeof(word_t))));
				kev++;
			}
			if(p != NULL)
				p->nu++;
		}
	}
	
	return head_2;
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	word_t * p = NULL;

	if((fp = fopen("./t.txt", "r")) == NULL)
	{
		fprintf(stderr, "Usage : open file<t.txt> error: %s!\n", strerror(errno));
		exit(1);
	}

	p = count_word_2(fp);
	for(; p != NULL; p = p->next)
	{
		printf("%s\t%d\n", p->name, p->nu);
	}

//	destory_2();



	fclose(fp);

	return 0;
}
