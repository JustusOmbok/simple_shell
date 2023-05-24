#include "shell.h"
#define BUFSIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

extern char **environ;

char *read_line(void);
char **parse_line(char *line);
char *find_path(char *command, char **paths);
int execute(char **args);
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
	int status;

	do{
		printf("$ ");
		line = read_line();
		args = parse_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);

	return EXIT_SUCCESS;
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
 * **parse_line - parses line
 * bufsize: bufsize
 * position: position
 * **tokens: tokens
 * *token: token
 * Return: tokens
 */

char **parse_line(char *line)
{
	int bufsize = BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens) {
		perror("parse_line");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens) {
				perror("parse_line");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;

	return tokens;
}

/**
 * *find_path - finds path
 * *path: path
 * *temp: temp
 * i: i
 * Return: NULL
 */

char *find_path(char *command, char **paths)
{
	char *path;
	char *temp;
	int i;

	for (i = 0; paths[i] != NULL; i++) {
		path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (!path) {
			perror("find_path");
			exit(EXIT_FAILURE);
		}

		sprintf(path, "%s/%s", paths[i], command);
		temp = strdup(path);
		free(path);

		if (access(temp, X_OK) == 0) {
			return temp;
		}

		free(temp);
	}

	return NULL;
}

/**
 * execute - execute
 * pid: pid
 * wpid: wpid
 * status: status;
 * *path: path
 * Return: free path
 */

int execute(char **args)
{
	pid_t pid, wpid;
	int status;
	char *path;

	if (args[0] == NULL) {
		return 1;
	}

	path = find_path(args[0], environ);
	if (path == NULL) {
		printf("%s: command not found\n", args[0]);
		return 1;
	}

	pid = fork();
	if (pid == -1) {
		perror("execute");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		if (execve(path, args, environ) == -1) {
			perror("execute");
		}
		exit(EXIT_FAILURE);
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
			if (wpid == -1) {
				perror("execute");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(path);

	return 0;
}
