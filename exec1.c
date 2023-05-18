#include "shell.h"

/**
 * execute_command - executes command
 * pid: pid
 * status: status
 * Return: EXIT_SUCCESS
 */

int execute_command(char **args)
{
	pid_t pid, wpid;
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

		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return EXIT_SUCCESS;
}
