#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - builtin command that either prints all aliases, specific
 *	aliases, or sets an alias.
 * @args: array of arguments.
 * @front: double pointer to the beginning of args.
 *
 * Return: -1 if an error occurs.
 *         otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int k, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (k = 0; args[k]; k++)
	{
		temp = aliases;
		value = _strchr(args[k], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[k], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + k, 1);
		}
		else
			set_alias(args[k], value);
	}
	return (ret);
}

/**
 * set_alias - will either set an existing alias 'name' with a new value,
 *	'value' or creates a new alias with 'name' and 'value'.
 * @var_name: name of the alias.
 * @value: value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, i, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (i = 0, k = 0; value[i]; i++)
	{
		if (value[i] != '\'' && value[i] != '"')
			new_value[k++] = value[i];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - prints the alias in the format name='value'.
 * @alias: pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - searches through the arguments and replace any
 *	matching alias with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int k;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (k = 0; args[k]; k++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[k], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[k]);
				args[k] = new_value;
				k--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
