#include "shell.h"

/**
 * _strcpy - func that copies a string
 * @dest: the ptr to the destination
 * @src: the ptr to the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
/**
 * _strdup - func that duplicates a string
 * @str: the string to be duplicated
 *
 * Return: the pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	dup = malloc(sizeof(char) * (length + 1));
	if (!dup)
		return (NULL);
	for (length++; length--;)
		dup[length] = *--str;
	return (dup);
}
/**
 *_puts - funct that prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}
/**
 * _putchar - func that writes the character c to stdout
 * @c: The character to print to stdout
 *
 * Return: 1 on success,
 * 	-1 on error, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
