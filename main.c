#include "shell.h"

/**
 * main - entry
 * *line - null
 * len = length of string
 * read: reads input
 * Return: exit if success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid = fork();

	while (1) {
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1) {
			break;
		}

		if (line[read - 1] == '\n'){
			line[read - 1] = '\0';
		}

		if (pid == -1) {
			perror("fork");
			continue;
		}
		if (pid == 0) {
			execlp(line, line, (char *)NULL);
			perror(line);
			exit(EXIT_FAILURE);
		} else {
			int status;
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}
