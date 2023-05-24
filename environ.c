#include "shell.h"

/**
 * execute - execute
 * pid: pid
 * status: status
 * i: i
 */

void execute_environ(char **argv)
{
	pid_t pid;
	int status;
	int i = 0;

	if (argv[0] == NULL)
		exit(EXIT_FAILURE);

	pid = fork();
	if (pid == -1)
		perror("Error");
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			if (strcmp(argv[0], "env") == 0)
			{

				while (environ[i])
				{
					printf("%s\n", environ[i]);
					i++;
				}
				exit(EXIT_SUCCESS);
			}
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}

/**
 * main - main
 * args: args
 * Return: 0
 */
int main()
{
	char* args[] = {"ls", "-1", NULL};

	execute_environ(args);

	return 0;
}
