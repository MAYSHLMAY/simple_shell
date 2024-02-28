#include "headers/Shell_Header.h"

/**
 * shell_exit - exiting
 * @form: Struct with pot args
 * Return: exit status (0)
*/

int shell_exit(form_t *form)
{
	int e_code;

	if (form->argv[1])
	{
		e_code = _error_atoi(form->argv[1]);
		if (e_code == -1)
		{
			form->status = 2;
			pr_erro(form, ":( ");
			_error_puts(form->argv[1]);
			my_putchar('\n');
			return (1);
		}
		form->err_num = e_code;
		return (-2);
	}
	form->err_num = -1;
	return (-2);
}

/**
 * _my_cd_cmd - changes the current directory
 * @form: Structure contains potential args
 *
 * Return: Always (0)
 */

int _my_cd_cmd(form_t *form)
{
	char *cwd, buffer[1024];
	int chdir_result;

	cwd = getcwd(buffer, 1024);
	if (!form->argv[1])
	{
		if (_getenv(form, "HOME="))
			chdir_result = chdir(_getenv(form, "HOME="));
		else
			chdir_result = chdir("/");
	}
	else if (my_strcmp(form->argv[1], "-") == 0)
	{
		if (!_getenv(form, "OLDPWD="))
		{
			my_puts(cwd);
			my_putchar('\n');
			return (1);
		}
		my_puts(_getenv(form, "OLDPWD="));
		my_putchar('\n');
		chdir_result = chdir(_getenv(form, "OLDPWD="));
	}
	else
		chdir_result = chdir(form->argv[1]);

	if (chdir_result == -1)
	{
		pr_erro(form, "can't change directory ");
		_error_puts(form->argv[1]);
		my_putchar('\n');
	}
	else
	{
		_setenv(form, "OLDPWD", _getenv(form, "PWD="));
		_setenv(form, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @form: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(form_t *form)
{
	print_list(form->history);
	return (0);
}


