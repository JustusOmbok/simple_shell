#include "shell.h"

/**
 * tokenize_input - input is tokenized
 * token: tokens
 * Return: tokens
 */
char **tokenize_input(char *input)
{
	int TOKEN_BUFSIZE = 100;
	char *token;
	int token_count = 0;

	char **tokens = malloc(sizeof(char *) * TOKEN_BUFSIZE);
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}


	token = strtok(input, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[token_count] = token;
		token_count++;

		if (token_count >= TOKEN_BUFSIZE)
		{
			fprintf(stderr, "Too many arguments\n");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[token_count] = NULL;
	return tokens;
}

