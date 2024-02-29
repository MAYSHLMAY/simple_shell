#include "headers/Shell_Header.h"

/**
 * main - entry point
 * @argc: arg count
 * @arg_v: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **arg_v)
{
	flex_t form[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=rms" (fd)
		: "rms" (fd));

	if (argc == 2)
	{
		fd = open(arg_v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_error_puts(arg_v[0]);
				_error_puts(": 0: Can't open ");
				_error_puts(arg_v[1]);
				my_putchar('\n');
				my_putchar(B_F);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		form->readfd = fd;
	}
	populate_env_list(form);
	read_history(form);
	exe_shell(form, arg_v);
	return (EXIT_SUCCESS);
}
