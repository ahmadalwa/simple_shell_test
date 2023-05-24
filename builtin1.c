#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 * @info: Structure containing potential arguments. Used to maintain
 *  with line numbers, starting at 0.
 *  constant function prototype.
 *  Return: Always 0
 */

int _myhistory(informt *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetaliased - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unsetaliased(informt *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setaliases - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int setaliases(informt *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetaliased(info, str));

	unsetaliased(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printsalias - prints an alias string
 * @node: the alias nod
 * Return: Always 0 on success, 1 on error
 */
int printsalias(listto *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 *  Return: Always 0
 */
int _myalias(informt *info)
{
	int i = 0;
	char *p = NULL;
	listto *node = NULL;

	if (info->argoc == 1)
	{
		node = info->alias;
		while (node)
		{
			printsalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argov[i]; i++)
	{
		p = _strchr(info->argov[i], '=');
		if (p)
			setaliases(info, info->argov[i]);
		else
			printsalias(node_starts_with(info->alias, info->argov[i], '='));
	}

	return (0);
}

