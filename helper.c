#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - frees up memory taken by args.
 * @args: null-terminated double pointer containing commands/arguments.
 * @front: double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - gets the current process id.
 * Description: opens the stat file, a space-delimited file containing
 *              information about the current process. The pid is the
 *              first word in the file. The function reads the pid into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: current process id or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - gets the value corresponding to an environmental variable.
 * @beginning: environmental variable to search for.
 * @len: length of the environmental variable to search for.
 *
 * Return: an empty string if the variable is not found.
 *         otherwise - the value of the environmental variable.
 *
 * Description: variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - handles variable replacement.
 * @line: double pointer containing the command and arguments.
 * @exe_ret: pointer to the return value of the last executed command.
 *
 * Description: replaces $$ with the current pid, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int i, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		if (old_line[i] == '$' && old_line[i + 1] &&
				old_line[i + 1] != ' ')
		{
			if (old_line[i + 1] == '$')
			{
				replacement = get_pid();
				k = i + 2;
			}
			else if (old_line[i + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = i + 2;
			}
			else if (old_line[i + 1])
			{
				/* extract the variable name to search for */
				for (k = i + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (i + 1);
				replacement = get_env_value(&old_line[i + 1], len);
			}
			new_line = malloc(i + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, i);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			i = -1;
		}
	}
}
