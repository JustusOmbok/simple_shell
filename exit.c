#include "shell.h"
#define MAX_ARGS 64

/**
 * main - main
 * *line: line
 * **args: args
 * status: status
 * Return: EXIT_SUCCESS
 */

int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		printf("($) ");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	}

	return (EXIT_SUCCESS);
}

/**
 * execute - executes
 * @i: i
 * @j: j
 * @*command: pointer
 * @**path: pointer
 * Return: 1
 */

int execute(char **args)
{
	int i;
	char *command;
	char **path;
	struct stat st;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	path = get_path();
	command = malloc(sizeof(char) * 1024);

	for (i = 0; path[i] != NULL; i++)
	{
		strcpy(command, path[i]);
		strcat(command, "/");
		strcat(command, args[0]);

		if (stat(command, &st) == 0)
		{
			if (fork() == 0)
			{
				execve(command, args, environ);
			}
			else
			{
				wait(NULL);
				free(command);
				free(path);
				return (1);
			}
		}
	}

	printf("%s: command not found\n", args[0]);
	free(command);
	free(path);
	return (1);
}

/**
 * *read_line - reads line
 * *line: line
 * bufsize: bufsize
 * Return: line
 */

char *read_line(void)
{
        char *line = NULL;
        size_t bufsize = 0;

        if (getline(&line, &bufsize, stdin) == -1) {
                if (feof(stdin)) {
                        exit(EXIT_SUCCESS);
                } else {
                        perror("read_line");
                        exit(EXIT_FAILURE);
                }
        }

        return line;
}

/**
 * **split_line - splits a line
 * @**args: args
 * @*token: token
 * 
 * @i: i
 * @line: line
 * Return: args
 */

char **split_line(char *line)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int i = 0;

	if (args == NULL) {
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n");
	while (token != NULL && i < MAX_ARGS -1) {
		args[i] = strdup(token);
		token = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;

	return args;
}

/**
 * get_path - gets path
 * @pathEnv: path
 * Return: path
 */
char** get_path()
{
	char* pathEnv = getenv("PATH");
	int numPaths = 1;
	int i = 0;
	char** path = malloc((numPaths + 1) * sizeof(char*));
	char* token = strtok(pathEnv, ":");

	if (pathEnv == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found.\n");
		return NULL;
	}


	for (i = 0; pathEnv[i] != '\0'; i++)
	{
		if (pathEnv[i] == ':')
		{
			numPaths++;
		}
	}


	while (token != NULL)
	{
		path[i] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(path[i], token);
		i++;

		token = strtok(NULL, ":");
	}

	path[i] = NULL;

	return path;
}
