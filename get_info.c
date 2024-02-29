#include "headers/Shell_Header.h"

/**
 * clear_info - initializes form_t struct
 * @form: struct address
 */
void clear_info(form_t *form)
{
	form->arg = NULL;
	form->argv = NULL;
	form->path = NULL;
	form->argc = 0;
}

/**
 * set_info - initializes form_t struct
 * @form: struct address
 * @argv: argument vector
 */
void set_info(form_t *form, char **argv)
{
	int i = 0;

	form->fname = argv[0];
	if (form->arg)
	{
		form->argv = strtow(form->arg, " \t");
		if (!form->argv)
		{

			form->argv = malloc(sizeof(char *) * 2);
			if (form->argv)
			{
				form->argv[0] = my_strdup(form->arg);
				form->argv[1] = NULL;
			}
		}
		for (i = 0; form->argv && form->argv[i]; i++)
			;
		form->argc = i;

		replace_vars(form);
	}
}

/**
 * free_info - frees form_t struct fields
 * @form: struct address
 * @all: true if freeing all fields
 */
void free_info(form_t *form, int all)
{
	free_string_array(form->argv);
	form->argv = NULL;
	form->path = NULL;
	if (all)
	{
		if (!form->cmd_buf)
			free(form->arg);
		if (form->env)
			free_list(&(form->env));
		if (form->history)
			free_list(&(form->history));
		free_string_array(form->environ);
			form->environ = NULL;
		free_and_null((void **)form->cmd_buf);
		if (form->readfd > 2)
			close(form->readfd);
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
	static int i;
	static char buf[W_B_S];

	if (c == B_F || i >= W_B_S)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != B_F)
		buf[i++] = c;
	return (1);
}
