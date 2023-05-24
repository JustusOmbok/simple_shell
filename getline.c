#include "shell.h"
#define BUFSIZE 1024
/**
 * my_getline - gets line
 * buffer[BUFSIZE]: bufsize
 * pos: pos
 * c: c
 * Return: NULL
 */

char *my_getline(void)
{
	static char buffer[BUFSIZE];
	static int pos;
		int c;

		while (1)
		{
			c = getchar();
			if (c == EOF || c == '\n')
			{
				buffer[pos] = '\0';
				pos = 0;
				return buffer;
			}
			else
			{
				buffer[pos++] = c;
				if (pos >= BUFSIZE)
				{
					fprintf(stderr, "Input too long\n");
					pos = 0;
					return NULL;
				}
			}
		}
}
