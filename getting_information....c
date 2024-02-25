#include "Shell_Header.h"

/**
 * clear_info - initializes information_t struct
 * @info: struct address
 */
void clear_info(information_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes information_t struct
 * @info: struct address
 * @argv: argument vector
 */
void set_info(information_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = my_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees information_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(information_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
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
		free_string_array(info->environ);
			info->environ = NULL;
		free_and_null((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		my_putchar(BUF_FLUSH);
	}
}
