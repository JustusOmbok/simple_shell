#include "shell.h"

/**
 *_eputs - func that prints an input string
 * @str: the string to be printed out
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - func that writes the character c to stderr
 * @c: char to be printed
 *
 * Return: On success 1, -1 on error, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - func writes the character c to given fd
 * @c: char to print
 * @fd: filedescriptor to write to
 *
 * Return: On succ 1, -1 on error, -1 and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 *_putsfd - func that prints an input string
 * @str: string to be printed
 * @fd: the filedescriptor to write onto
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int  k= 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
