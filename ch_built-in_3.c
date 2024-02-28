#include "headers/Shell_Header.h"

/**
 * check_chain - checks we should continue chaining based on last status
 * @form: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(form_t *form, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (form->cmd_buf_type == C_AND)
	{
		if (form->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (form->cmd_buf_type == C_OR)
	{
		if (!form->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @form: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(form_t *form)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(form->alias, form->argv[0], '=');
		if (!node)
			return (0);
		free(form->argv[0]);
		p = my_strchr(node->str, '=');
		if (!p)
			return (0);
		p = my_strdup(p + 1);
		if (!p)
			return (0);
		form->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @form: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(form_t *form)
{
	int i = 0;
	list_t *node;

	for (i = 0; form->argv[i]; i++)
	{
		if (form->argv[i][0] != '$' || !form->argv[i][1])
			continue;

		if (!my_strcmp(form->argv[i], "$?"))
		{
			replace_string(&(form->argv[i]),
				my_strdup(convert_number(form->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(form->argv[i], "$$"))
		{
			replace_string(&(form->argv[i]),
				my_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(form->env, &form->argv[i][1], '=');
		if (node)
		{
			replace_string(&(form->argv[i]),
				my_strdup(my_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&form->argv[i], my_strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
