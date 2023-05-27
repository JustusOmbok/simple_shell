#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - prints the current environment.
 * @args: array of arguments passed to the shell.
 * @front: double pointer to the beginning of args.
 *
 * Return: -1 if an error occurs.
 *	   otherwise - 0.
 *
 * Description: prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int indx;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (indx = 0; environ[indx]; indx++)
	{
		write(STDOUT_FILENO, environ[indx], _strlen(environ[indx]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - changes or adds an environmental variable to the PATH.
 * @args: array of arguments passed to the shell.
 * @front: double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return:  -1 if an error occurs.
 *         otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int indx;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (indx = 0; environ[indx]; indx++)
		new_environ[indx] = environ[indx];

	free(environ);
	environ = new_environ;
	environ[indx] = new_value;
	environ[indx + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - deletes an environmental variable from the PATH.
 * @args: array of arguments passed to the shell.
 * @front: double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: -1 if an error occurs.
 *         otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int indx, indx2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (indx = 0, indx2 = 0; environ[indx]; indx++)
	{
		if (*env_var == environ[indx])
		{
			free(*env_var);
			continue;
		}
		new_environ[indx2] = environ[indx];
		indx2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
