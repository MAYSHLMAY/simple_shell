#include "headers/Shell_Header.h"

/**
 * _myenv - prints the current environment
 * @fm: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(flex_t *fm)
{
	print_list_str(fm->env);
	return (0);
}

/**
 * my_getenv - gets the value of an environ variable
 * @fm: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *my_getenv(flex_t *fm, const char *name)
{
	histo_t *nde = fm->env;
	char *par;

	while (nde)
	{
		par = starts_with(nde->c_r, name);
		if (par && *par)
			return (par);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @fm: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(flex_t *fm)
{
	if (fm->argc != 3)
	{
		_error_puts("Incorrect Num of args\n");
		return (1);
	}
	if (_setenv(fm, fm->arg_o_v[1], fm->arg_o_v[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @fm: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(flex_t *fm)
{
	int p1;

	if (fm->argc == 1)
	{
		_error_puts("Too few arguements.\n");
		return (1);
	}
	for (p1 = 1; p1 <= fm->argc; p1++)
		_unsetenv(fm, fm->arg_o_v[p1]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @fm: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(flex_t *fm)
{
	histo_t *nde = NULL;
	size_t p1;

	for (p1 = 0; environ[p1]; p1++)
		add_node_end(&nde, environ[p1], 0);
	fm->env = nde;
	return (0);
}
