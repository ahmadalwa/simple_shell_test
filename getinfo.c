i#include "shell.h"

/**
 * clear_info - initializes (informt struct
 * @info: struct address
 */
void clear_info(informt *info)
{
	info->argo= NULL;
	info->argov = NULL;
	info->path = NULL;
	info->argoc = 0;
}

/**
 * set_info - initializes (informt struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(informt *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argov = strtow(info->arg, " \t");
		if (!info->argov)
		{
			info->argov = malloc(sizeof(char *) * 2);
			if (info->argov)
			{
				info->argov[0] = _strdup(info->arg);
				info->argov[1] = NULL;
			}
		}
		for (i = 0; info->argov && info->argov[i]; i++)
			;
		info->argoc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees (informt struct fields
 * @info: struct addres
 * @all: true if freeing all fields
 */
void free_info(informt *info, int all)
{
	ffree(info->argov);
	info->argov = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
