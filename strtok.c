#include "shell.h"

#define BUFFER_SIZE 1024
/**
 * main - main
 * buffer: buffer
 * argv: argv
 * argc: argc
 * read_count: read count
 * token: token
 * next_token: token
 */
extern char **environ;

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *argv[100];
	size_t argc;
	ssize_t read_count;
	 char **env;
	char *token, *next_token;

	while (1)
	{
		printf("$ ");
		read_count = read(STDIN_FILENO, buffer, BUFFER_SIZE);

		if (read_count == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (read_count == 0)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		if (buffer[read_count - 1] == '\n')
		{
			buffer[read_count - 1] = '\0';
		}
		else
		{
			buffer[read_count] = '\0';
		}

		argc = 0;
		token = buffer;

		while (*token)
		{
			next_token = strchr(token, ' ');

			if (next_token)
			{
				*next_token = '\0';
				next_token++;
			}

			argv[argc++] = token;
			token = next_token;
		}

		argv[argc] = NULL;

		if (argc > 0)
		{
			if (strcmp(argv[0], "exit") == 0)
			{
				exit(EXIT_SUCCESS);
			}
			else if (strcmp(argv[0], "env") == 0)
			{
				env = environ;


				while (*env)
				{
					printf("%s\n", *env++);
				}
			}
			else
			{
				pid_t pid = fork();

				if (pid == -1)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}

				if (pid == 0)
				{
					execve(argv[0], argv, NULL);
					perror("execve");
					exit(EXIT_FAILURE);
				}

				wait(NULL);
			}
		}
	}

	return 0;
}
