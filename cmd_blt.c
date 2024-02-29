#include "headers/Shell_Header.h"

/**
 * exe_shell - main shell loop
 * @fm: the parameter & return fm struct
 * @arg_o_v: the argument vector from main()
 * Return: 0 / 1
 */
int exe_shell(flex_t *fm, char **arg_o_v)
{
	ssize_t rms;
	int bt_ret = 0;

	for (rms = 0; rms != -1 && bt_ret != -2;)
	{
		clear_info(fm);
		if (c_promp(fm))
			my_puts("$ ");
		my_putchar(B_F);
		rms = get_input(fm);
		if (rms != -1)
		{
			set_info(fm, arg_o_v);
			bt_ret = find_builtin(fm);
			if (bt_ret == -1)
				find_cmd(fm);
			free_info(fm, 0);
		}
		else if (c_promp(fm))
			my_putchar('\n');
	}

	write_history(fm);
	free_info(fm, 1);
	if (!c_promp(fm) && fm->status)
		exit(fm->status);
	if (bt_ret == -2)
	{
		if (fm->err_num == -1)
			exit(fm->status);
		exit(fm->err_num);
	}
	return (bt_ret);
}

/**
 * find_builtin - finds a builtin
 * @fm: the parameter & return fm struct
 *
 * Return: -1 if not found,
 *			0 if executed successfully,
 *			1 if found but not successful,
 *			-2 if exit()
 */
int find_builtin(flex_t *fm)
{
	int p1, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", _myenv},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _my_cd_cmd},
		{NULL, NULL}
	};

	for (p1 = 0; builtintbl[p1].type; p1++)
		if (my_strcmp(fm->arg_o_v[0], builtintbl[p1].type) == 0)
		{
			fm->line_count++;
			built_in_ret = builtintbl[p1].func(fm);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @fm: the parameter & return fm struct
 *
 * Return: void
 */
void find_cmd(flex_t *fm)
{
	char *path = NULL;
	int p1, p3;

	fm->path = fm->arg_o_v[0];
	if (fm->linecount_flag == 1)
	{
		fm->line_count++;
		fm->linecount_flag = 0;
	}
	for (p1 = 0, p3 = 0; fm->arg[p1]; p1++)
		if (!ch_del(fm->arg[p1], " \t\n"))
			p3++;
	if (!p3)
		return;
	path = find_path(fm, my_getenv(fm, "PATH="), fm->arg_o_v[0]);
	if (path)
	{
		fm->path = path;
		fork_cmd(fm);
	}
	else
	{
		int cs = c_promp(fm) || my_getenv(fm, "PATH=") || fm->arg_o_v[0][0] == '/';

		switch (cs)
		{
			case 1:
				if (is_cmd(fm, fm->arg_o_v[0]))
					fork_cmd(fm);
				break;
			case 0:
				if (*(fm->arg) != '\n')
				{
					fm->status = 127;
					pr_erro(fm, "not found:(\n");
				}
				break;
			default:
				break;
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @fm: the parameter & return fm struct
 *
 * Return: void
 */
void fork_cmd(flex_t *fm)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(fm->path, fm->arg_o_v, get_environ(fm)) == -1)
		{
			free_info(fm, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(fm->status));
		if (WIFEXITED(fm->status))
		{
			fm->status = WEXITSTATUS(fm->status);
			if (fm->status == 126)
				pr_erro(fm, "Permission denied\n");
		}
	}
}
