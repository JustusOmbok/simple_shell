split.c
#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - func that locates the delimiter index
 *             marking the endof the first token
 *		contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int indx = 0, len = 0;

	while (*(str + indx) && *(str + indx) != *delim)
	{
		len++;
		indx++;
	}

	return (len);
}

/**
 * count_tokens - counts the number of delimited
 *                words contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int indx, tokens = 0, len = 0;

	for (indx = 0; *(str + indx); indx++)
		len++;

	for (index = 0; indx < len; indx++)
	{
		if (*(str + indx) != *delim)
		{
			tokens++;
			indx += token_len(str + indx, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - tokenizes a string.
 * @line: the string.
 * @delim: delimiter character to tokenize the string by.
 *
 * Return: pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int indx = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[indx] == *delim)
			indx++;

		letters = token_len(line + indx, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (indx -= 1; indx >= 0; indx--)
				free(ptr[indx]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[indx];
			indx++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
