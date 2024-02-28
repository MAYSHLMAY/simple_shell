#include "headers/Shell_Header.h"

/**
 * _myenv - prints the current environment
 * @form: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(form_t *form)
{
	print_list_str(form->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @form: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(form_t *form, const char *name)
{
	list_t *node = form->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @form: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(form_t *form)
{
	if (form->argc != 3)
	{
		_error_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(form, form->argv[1], form->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @form: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(form_t *form)
{
	int i;

	if (form->argc == 1)
	{
		_error_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= form->argc; i++)
		_unsetenv(form, form->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @form: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(form_t *form)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	form->env = node;
	return (0);
}
