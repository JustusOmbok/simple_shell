#include "shell.h"

/**
 * **strtow - splits a giving string into words. Repeated delimiters
 *	are ignored
 * @str: the input string to split
 * @d: the delimeter string
 * Return: pointer to the array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int u, v, w, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (u = 0; str[u] != '\0'; u++)
		if (!is_delim(str[u], d) && (is_delim(str[u + 1], d) || !str[u + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (u = 0, v = 0; v < numwords; v++)
	{
		while (is_delim(str[u], d))
			u++;
		w = 0;
		while (!is_delim(str[u + w], d) && str[u + w])
			w++;
		s[v] = malloc((w + 1) * sizeof(char));
		if (!s[v])
		{
			for (w = 0; w < v; w++)
				free(s[w]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < w; m++)
			s[v][m] = str[u++];
		s[v][m] = 0;
	}
	s[v] = NULL;
	return (s);
}

/**
 * **strtow2 - func that splits a string into words
 * @str: the input string to split
 * @d: the delimeter string
 * Return: pointer to the array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int u, v, w, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (u = 0; str[u] != '\0'; u++)
		if ((str[u] != d && str[u + 1] == d) ||
		    (str[u] != d && !str[u + 1]) || str[u + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (u = 0, v = 0; v < numwords; v++)
	{
		while (str[u] == d && str[u] != d)
			u++;
		w = 0;
		while (str[u + w] != d && str[u + w] && str[u + w] != d)
			w++;
		s[v] = malloc((w + 1) * sizeof(char));
		if (!s[v])
		{
			for (w = 0; w < v; w++)
				free(s[w]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < w; m++)
			s[v][m] = str[u++];
		s[v][m] = 0;
	}
	s[v] = NULL;
	return (s);
}
