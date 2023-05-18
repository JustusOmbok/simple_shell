#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#define EXIT_EOF -1
/**
 * main - entry
 * *input: input
 * **args: args
 * status: status
 */
char read_input(void);

int main(int argc, char *argv[])
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
			perror(argv[0]);
		else if (status == EXIT_EOF)
			break;
	}

	return EXIT_SUCCESS;
}
