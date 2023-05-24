#include "shell.h"

#define EXIT_EOF -1
#define MAX_INPUT_LENGTH 1024
/**
 * main - entry
 * *input: input
 * **args: args
 * status: status
 */

int main(void)
{
        char *input;
        char **args;
        int status;
        input = read_input();
        args = tokenize_input(input);
        status = execute_command(args);

        while (1)
        {
                free(input);
                free(args);

                if (status == EXIT_SUCCESS)
                        continue;
                else if (status == EXIT_FAILURE)
                        perror("Error executing command");
                else if (status == EXIT_EOF)
			  break;
        }

        return EXIT_SUCCESS;
}

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

/**
 * read_input - reads input
 * input: input
 * Return: input
 */

char* read_input()
{
	char* input = malloc(MAX_INPUT_LENGTH * sizeof(char));

	if (input == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	printf("Enter a command: ");
	fgets(input, MAX_INPUT_LENGTH, stdin);

	return input;
}

/**
 * execute_command - executes
 * pid: pid
 * wpid:w pid
 * Return: EXIT_SUCCESS
 */

int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return EXIT_SUCCESS;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (waitpid(pid, &status, WUNTRACED) == -1) 
		{
			if (errno != EINTR)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}
