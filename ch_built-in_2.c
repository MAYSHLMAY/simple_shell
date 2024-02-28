#include "headers/Shell_Header.h"


/**
 * unset_alias - sets alias to string
 * @form: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(form_t *form, char *str)
{
	char *p, c;
	int ret;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(form->alias),
		get_node_index(form->alias, node_starts_with(form->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @form: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(form_t *form, char *str)
{
	char *p;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(form, str));

	unset_alias(form, str);
	return (add_node_end(&(form->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = my_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			my_putchar(*a);
		my_putchar('\'');
		my_puts(p + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - mimics the alias builtin (man alias)
 * @form: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int alias_command(form_t *form)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (form->argc == 1)
	{
		node = form->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; form->argv[i]; i++)
	{
		p = my_strchr(form->argv[i], '=');
		if (p)
			set_alias(form, form->argv[i]);
		else
			print_alias(node_starts_with(form->alias, form->argv[i], '='));
	}

	return (0);
}

/**
 * c_promp - returns true if shell is interactive mode
 * @form: struct address
 *
 * Return: 1 if c_promp mode, 0 otherwise
 */
int c_promp(form_t *form)
{
	return (isatty(STDIN_FILENO) && form->readfd <= 2);
}



