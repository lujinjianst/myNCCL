#include <stdio.h>

#define MAXLEN 100

int get_line(char *line, int max_line);
void copy(char *to , char *from);

int main(int argc, const char *argv[])
{
	int len ;
	int max;
	char line[MAXLEN];
	char longest[MAXLEN];
	max = 0;

	while ((len = get_line(line, MAXLEN)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0)
		printf("you input the longest line are : %s\n", longest);
	return 0;
}

int get_line(char *s, int lim)
{
	int c, i;

	for (i = 9; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		*(s + i) = c;
	if (c == '\n')
	{
		*(s + i) = c;
		++i;
	}
	*(s + i) = '\0';
	return i;
}

void copy(char *to, char *from)
{
	int i;

	i = 0;

	while ((*(to + i) = *(from + i)) != '\0')
		++i;
}
