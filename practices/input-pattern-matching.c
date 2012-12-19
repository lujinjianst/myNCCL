#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXLEN  100

int get_line(char s[], int lim);

int main(int argc, const char *argv[])
{
	char line[MAXLINE];
	char *buf[MAXLINE];
	long lineno = 0;
	long i;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv) [0] == '-')
	{
		while (c = *++argv[0])
		{
			switch (c)
			{
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find : illegal options %c\n", c);
					argc = 0;
					found = -1;
			}
		}
	}

	if (argc != 1)
	{
		printf("usage: find -x -n pattern-matching\n");
		exit(1);
	}
	else
	{
		while (get_line(line,MAXLEN) > 0)
		{
			buf[lineno] = (char *)malloc(strlen(line) + 1);
			strcpy(buf[lineno], line);
			lineno++;
		}
		i = 0;
		printf("matching result:\n");
		while (i < lineno)
		{
			if ((strstr(buf[i], *argv) != NULL) != except)
			{
				if (number)
					printf("%ld:", i + 1);
				found++;
			}
			i++;
		}
	}
	printf("Input satisfied the pattern matching with %d line!", found);

	return found;
}

int get_line(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
			s[i] = c;
			++i;
	}
	s[i] = '\0';

	return i;
}

