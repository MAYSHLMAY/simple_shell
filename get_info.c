#include "headers/Shell_Header.h"

/**
 * clear_info - initializes flex_t struct
 * @fm: struct address
 */
void clear_info(flex_t *fm)
{
	fm->arg = NULL;
	fm->arg_o_v = NULL;
	fm->path = NULL;
	fm->argc = 0;
}

/**
 * set_info - initializes flex_t struct
 * @fm: struct address
 * @arg_o_v: argument vector
 */
void set_info(flex_t *fm, char **arg_o_v)
{
	int p1 = 0;

	fm->fname = arg_o_v[0];
	if (fm->arg)
	{
		fm->arg_o_v = my_spx(fm->arg, " \t");
		if (!fm->arg_o_v)
		{

			fm->arg_o_v = malloc(sizeof(char *) * 2);
			if (fm->arg_o_v)
			{
				fm->arg_o_v[0] = my_strdup(fm->arg);
				fm->arg_o_v[1] = NULL;
			}
		}
		for (p1 = 0; fm->arg_o_v && fm->arg_o_v[p1]; p1++)
			;
		fm->argc = p1;

		replace_vars(fm);
	}
}

/**
 * free_info - frees flex_t struct fields
 * @fm: struct address
 * @all: true if freeing all fields
 */
void free_info(flex_t *fm, int all)
{
	free_string_array(fm->arg_o_v);
	fm->arg_o_v = NULL;
	fm->path = NULL;
	if (all)
	{
		if (!fm->cmd_buf)
			free(fm->arg);
		if (fm->env)
			free_list(&(fm->env));
		if (fm->history)
			free_list(&(fm->history));
		free_string_array(fm->environ);
			fm->environ = NULL;
		free_and_null((void **)fm->cmd_buf);
		if (fm->readfd > 2)
			close(fm->readfd);
		my_putchar(B_F);
	}
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int my_putchar(char c)
{
	static int p1;
	static char buf[W_B_S];

	if (c == B_F || p1 >= W_B_S)
	{
		write(1, buf, p1);
		p1 = 0;
	}
	if (c != B_F)
		buf[p1++] = c;
	return (1);
}
