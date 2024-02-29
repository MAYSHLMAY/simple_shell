#include "headers/Shell_Header.h"

/**
 * check_chain - checks we should
 * @fm: the parameter struct
 * @buf: the char buffer
 * @par: address of current position
 * @p1: starting position in buf
 * @lenz: length of buf
 *
 * Return: Void
 */

void check_chain(flex_t *fm, char *buf, size_t *par, size_t p1, size_t lenz)
{
	size_t p2 = *par;

	switch (fm->cmd_buf_type)
	{
		case C_AND:
			if (fm->status)
			{
				buf[p1] = 0;
				p2 = lenz;
			}
			break;
		case C_OR:
			if (!fm->status)
			{
				buf[p1] = 0;
				p2 = lenz;
			}
			break;
	}

	*par = p2;
}


/**
 * replace_vars - replaces vars
 * @fm: the parameter struct
 * Return: 1 / 0
 */
int replace_vars(flex_t *fm)
{
	int p1 = 0;
	histo_t *nde;

	for (p1 = 0; fm->arg_o_v[p1]; p1++)
	{
		if (fm->arg_o_v[p1][0] != '$' || !fm->arg_o_v[p1][1])
			continue;

check_variable:
		if (!my_strcmp(fm->arg_o_v[p1], "$?"))
		{
			replace_string(&(fm->arg_o_v[p1]),
			my_strdup(convert_number(fm->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(fm->arg_o_v[p1], "$$"))
		{
			replace_string(&(fm->arg_o_v[p1]),
			my_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nde = node_starts_with(fm->env, &fm->arg_o_v[p1][1], '=');
		if (nde)
		{
			replace_string(&(fm->arg_o_v[p1]),
			my_strdup(my_strchr(nde->c_r, '=') + 1));
			continue;
		}
		replace_string(&fm->arg_o_v[p1], my_strdup(""));

		goto check_variable;
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

/**
 * c_promp - returns true if shell is interactive mode
 * @fm: struct address
 *
 * Return: 1 if c_promp mode, 0 otherwise
 */
int c_promp(flex_t *fm)
{
	return (isatty(STDIN_FILENO) && fm->readfd <= 2);
}
