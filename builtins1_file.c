#include "shell.h"

/**
 * _myhistory - func that displays the history list, one
 *	 command by line, preceded with line numbers,
 *       starting at 0.
 * @info: Structure containing potential arguments used to maintain
 *        constant function prototype.
 *  Return: 0 always
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - funct that sets alias to string
 * @info: struct parameter
 * @str: the alias string
 *
 * Return: 0 always on success, or 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, k;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	k = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = k;
	return (ret);
}

/**
 * set_alias - func that sets alias to a string
 * @info: parameter struct
 * @str: the alias string
 *
 * Return: 0 lways on success, or 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - func that prints an alias string
 * @node: the node of the alias to print
 *
 * Return: Always 0 on success, or 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *a = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (a = node->str; a <= q; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - func that mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments used to maintain
 * 	constant function prototype.
 *  Return: 0 always
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
