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
 * replace_vars - replaces vars in the tokenized string
 * @form: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(form_t *form)
{
	int i = 0;
	histo_t *nde;

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
		nde = node_starts_with(form->env, &form->argv[i][1], '=');
		if (nde)
		{
			replace_string(&(form->argv[i]),
				my_strdup(my_strchr(nde->c_r, '=') + 1));
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
