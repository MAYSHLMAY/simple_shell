#include "headers/Shell_Header.h"

/**
 * get_environ - returns the string array copy of our environ
 * @fm: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(flex_t *fm)
{
	if (!fm->environ || fm->env_changed)
	{
		fm->environ = list_to_strings(fm->env);
		fm->env_changed = 0;
	}

	return (fm->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @fm: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(flex_t *fm, char *var)
{
	histo_t *nde = fm->env;
	size_t p1 = 0;
	char *par;

	if (!nde || !var)
		return (0);

	while (nde)
	{
		par = starts_with(nde->c_r, var);
		if (par && *par == '=')
		{
			fm->env_changed = delete_node_at_index(&(fm->env), p1);
			p1 = 0;
			nde = fm->env;
			continue;
		}
		nde = nde->next;
		p1++;
	}
	return (fm->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @fm: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(flex_t *fm, char *var, char *value)
{
	char *buf = NULL;
	histo_t *nde;
	char *par;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	my_strcpy(buf, var);
	my_strcat(buf, "=");
	my_strcat(buf, value);
	nde = fm->env;
	while (nde)
	{
		par = starts_with(nde->c_r, var);
		if (par && *par == '=')
		{
			free(nde->c_r);
			nde->c_r = buf;
			fm->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_node_end(&(fm->env), buf, 0);
	free(buf);
	fm->env_changed = 1;
	return (0);
}
