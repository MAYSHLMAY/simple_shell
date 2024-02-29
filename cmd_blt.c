#include "headers/Shell_Header.h"

/**
 * executable_shell - main shell loop
 * @form: the parameter & return form struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int executable_shell(form_t *form, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(form);
		if (c_promp(form))
			my_puts("$ ");
		my_putchar(B_F);
		r = get_input(form);
		if (r != -1)
		{
			set_info(form, argv);
			builtin_ret = find_builtin(form);
			if (builtin_ret == -1)
				find_cmd(form);
		}
		else if (c_promp(form))
			my_putchar('\n');
		free_info(form, 0);
	}
	write_history(form);
	free_info(form, 1);
	if (!c_promp(form) && form->status)
		exit(form->status);
	if (builtin_ret == -2)
	{
		if (form->err_num == -1)
			exit(form->status);
		exit(form->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @form: the parameter & return form struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(form_t *form)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", _myenv},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _my_cd_cmd},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (my_strcmp(form->argv[0], builtintbl[i].type) == 0)
		{
			form->line_count++;
			built_in_ret = builtintbl[i].func(form);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @form: the parameter & return form struct
 *
 * Return: void
 */
void find_cmd(form_t *form)
{
	char *path = NULL;
	int i, k;

	form->path = form->argv[0];
	if (form->linecount_flag == 1)
	{
		form->line_count++;
		form->linecount_flag = 0;
	}
	for (i = 0, k = 0; form->arg[i]; i++)
		if (!is_delimiter(form->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(form, my_getenv(form, "PATH="), form->argv[0]);
	if (path)
	{
		form->path = path;
		fork_cmd(form);
	}
	else
	{
		if ((c_promp(form) || my_getenv(form, "PATH=")
			|| form->argv[0][0] == '/') && is_cmd(form, form->argv[0]))
			fork_cmd(form);
		else if (*(form->arg) != '\n')
		{
			form->status = 127;
			pr_erro(form, "not found:(\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @form: the parameter & return form struct
 *
 * Return: void
 */
void fork_cmd(form_t *form)
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
		if (execve(form->path, form->argv, get_environ(form)) == -1)
		{
			free_info(form, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(form->status));
		if (WIFEXITED(form->status))
		{
			form->status = WEXITSTATUS(form->status);
			if (form->status == 126)
				pr_erro(form, "Permission denied\n");
		}
	}
}
