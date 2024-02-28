#include "headers/Shell_Header.h"

/**
 * get_environ - returns the string array copy of our environ
 * @form: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(form_t *form)
{
	if (!form->environ || form->env_changed)
	{
		form->environ = list_to_strings(form->env);
		form->env_changed = 0;
	}

	return (form->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @form: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(form_t *form, char *var)
{
	histo_t *nde = form->env;
	size_t i = 0;
	char *p;

	if (!nde || !var)
		return (0);

	while (nde)
	{
		p = starts_with(nde->c_r, var);
		if (p && *p == '=')
		{
			form->env_changed = delete_node_at_index(&(form->env), i);
			i = 0;
			nde = form->env;
			continue;
		}
		nde = nde->next;
		i++;
	}
	return (form->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @form: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(form_t *form, char *var, char *value)
{
	char *buf = NULL;
	histo_t *nde;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	my_strcpy(buf, var);
	my_strcat(buf, "=");
	my_strcat(buf, value);
	nde = form->env;
	while (nde)
	{
		p = starts_with(nde->c_r, var);
		if (p && *p == '=')
		{
			free(nde->c_r);
			nde->c_r = buf;
			form->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_node_end(&(form->env), buf, 0);
	free(buf);
	form->env_changed = 1;
	return (0);
}
