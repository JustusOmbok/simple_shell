#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - locates a character in a given string.
 * @s: string to be searched.
 * @c: character to be located.
 *
 * Return: a pointer to the first occurence if c is found.
 *         NULL if c is not found.
 */
char *_strchr(char *s, char c)
{
	int indx;

	for (indx = 0; s[indx]; indx++)
	{
		if (s[indx] == c)
			return (s + indx);
	}

	return (NULL);
}

/**
 * _strspn - gets the length of a prefix substring.
 * @s: string to be searched.
 * @accept: prefix to be measured.
 *
 * Return: number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int indx;

	while (*s)
	{
		for (indx = 0; accept[indx]; indx++)
		{
			if (*s == accept[indx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - ompares two strings.
 * @s1: first string to be compared.
 * @s2: second string to be compared.
 *
 * Return: positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - compare two strings.
 * @s1: pointer to a string.
 * @s2: pointer to a string.
 * @n: first n bytes of the strings to compare.
 *
 * Return: sess than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
