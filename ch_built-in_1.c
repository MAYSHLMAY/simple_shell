#include "headers/Shell_Header.h"

/**
 * shell_exit - exiting
 * @fm: Struct with pot args
 * Return: exit status (0)
*/

int shell_exit(flex_t *fm)
{
	int e_code;

	if (fm->arg_v[1])
	{
		e_code = _errorintu(fm->arg_v[1]);
		if (e_code == -1)
		{
			fm->status = 2;
			pr_erro(fm, ":( ");
			_error_puts(fm->arg_v[1]);
			my_putchar('\n');
			return (1);
		}
		fm->err_num = e_code;
		return (-2);
	}
	fm->err_num = -1;
	return (-2);
}

/**
 * _my_cd_cmd - change the ccd
 * @fm: Structure contains potential args
 *
 * Return: Always (0)
 */

int _my_cd_cmd(flex_t *fm)
{
	char *cwd, buffer[1024];
	int chdir_res;

	cwd = getcwd(buffer, 1024);
	if (!fm->arg_v[1])
	{
		if (my_gev(fm, "HOME="))
			chdir_res = chdir(my_gev(fm, "HOME="));
		else
			chdir_res = chdir("/");
	}
	else if (my_strcmp(fm->arg_v[1], "-") == 0)
	{
		if (!my_gev(fm, "OLDPWD="))
		{
			my_puts(cwd);
			my_putchar('\n');
			return (1);
		}
		my_puts(my_gev(fm, "OLDPWD="));
		my_putchar('\n');
		chdir_res = chdir(my_gev(fm, "OLDPWD="));
	}
	else
		chdir_res = chdir(fm->arg_v[1]);

	if (chdir_res == -1)
	{
		pr_erro(fm, "can't change .... ");
		_error_puts(fm->arg_v[1]);
		my_putchar('\n');
	}
	else
	{
		_setenv(fm, "OLDPWD", my_gev(fm, "PWD="));
		_setenv(fm, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _myhistory - displays the history list,
 * @fm: Structure containing ppotential Args
 *  Return: Always 0
 */
int _myhistory(flex_t *fm)
{
	print_list(fm->history);
	return (0);
}
