#include "headers/Shell_Header.h"

/**
 * _error_puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _error_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_error_putchar(str[i]);
		i++;
	}
}

/**
 * _error_putchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _error_putchar(char c)
{
	static int i;
	static char buf[W_B_S];

	if (c == B_F || i >= W_B_S)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != B_F)
		buf[i++] = c;
	return (1);
}

/**
 * _putfile_d - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putfile_d(char c, int file_descriptor)
{
	static int i;
	static char buf[W_B_S];

	if (c == B_F || i >= W_B_S)
	{
		write(file_descriptor, buf, i);
		i = 0;
	}
	if (c != B_F)
		buf[i++] = c;
	return (1);
}

/**
 * _puts_filed - Prints an input string.
 * @str: The string to be printed.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _puts_filed(char *str, int file_descriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfile_d(*str++, file_descriptor);
	}
	return (i);
}

/**
 * _error_atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 *         -1 on error.
 */
int _error_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

