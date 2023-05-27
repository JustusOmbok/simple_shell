#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - creates a copy of the environment.
 *
 * Return: NULL if an error occurs.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int indx;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (indx = 0; environ[indx]; indx++)
	{
		new_environ[indx] = malloc(_strlen(environ[indx]) + 1);

		if (!new_environ[indx])
		{
			for (indx--; indx >= 0; indx--)
				free(new_environ[indx]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[indx], environ[indx]);
	}
	new_environ[indx] = NULL;

	return (new_environ);
}

/**
 * free_env - frees the the environ copy.
 */
void free_env(void)
{
	int indx;

	for (indx = 0; environ[indx]; indx++)
		free(environ[indx]);
	free(environ);
}

/**
 * _getenv - gets an environmental variable from the PATH.
 * @var: name of the environmental variable to get.
 *
 * Return: NULL if the environmental variable does not exist.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int indx, len;

	len = _strlen(var);
	for (indx = 0; environ[indx]; indx++)
	{
		if (_strncmp(var, environ[indx], len) == 0)
			return (&environ[indx]);
	}

	return (NULL);
}
