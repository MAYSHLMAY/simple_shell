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


