#include "Shell_Header.h"

/**
 * shell_exit - exits the shell
 * @info: Structure containing potential arguments
 *
 * Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */

int shell_exit(information_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _error_atoi(info->argv[1]);	
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_error_puts(info->argv[1]);
			_error_putchar('\n');
			return (1);
		}
		info->error_number = exit_code;
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}

/**
 * _my_current_working_cd_cmd - changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */

int _my_current_working_cd_cmd(information_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_result;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		my_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_result = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			my_puts(cwd);
			my_putchar('\n');
			return (1);
		}
		my_puts(_getenv(info, "OLDPWD="));
		my_putchar('\n');
		chdir_result = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_error_puts(info->argv[1]);
		_error_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}



/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(information_t *info, char *str)
{
	char *p, c;
	int ret;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(information_t *info, char *str)
{
	char *p;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
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
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(information_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	my_puts("help call works. Function not yet implemented \n");
	if (0)
		my_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(information_t *info)
{
	print_list(info->history);
	return (0);
}


