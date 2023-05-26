#include "shell.h"

/**
 * get_environ - returns a copy of string array of the environ
 * @info: Structure containing potential arguments used to maintain
 *          constant function prototype.
 * Return: 0 Always
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - removes an environ variable
 * @info: Structure containing potential arguments used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, or 0 otherwise
 * @var: the property for string env var
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t k = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			k = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environ variable,
 *       or modifies an existing one
 * @info: Structure containing potential arguments used to maintain
 *        constant function prototype.
 * @var: the property for string env var
 * @value: the value for string env var
 *  Return: 0 Always
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0); 
}
