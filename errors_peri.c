#include "headers/Shell_Header.h"

/**
 * _error_puts - Prints an input string.
 * @c_r: The string to be printed.
 *
 * Return: Nothing.
 */
void _error_puts(char *c_r)
{
	int index;

	if (!c_r)
		return;
	for (index = 0; c_r[index] != '\0'; index++)
		my_putchar(c_r[index]);
}

/**
 * _putfile_d - Writes the character c 
 * @c: The character to print.
 * @file_d: The file descriptor to write to.
 *
 * Return: On success 1.
 */
int _putfile_d(char c, int file_d)
{
	static int p1;
	static char buf[W_B_S];

	if (c == B_F || p1 >= W_B_S)
	{
		write(file_d, buf, p1);
		p1 = 0;
	}
	if (c != B_F)
		buf[p1++] = c;
	return (1);
}

/**
 * _puts_filed - Prints an input string.
 * @c_r: The string to be printed.
 * @file_d: The file descriptor to write to.
 *
 * Return: The number of chars put.
 */
int _puts_filed(char *c_r, int file_d)
{
	int p1 = 0;

	if (!c_r)
		return (0);
	while (*c_r)
	{
		p1 += _putfile_d(*c_r++, file_d);
	}
	return (p1);
}

/**
 * _errorintu - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers 
 */
int _errorintu(char *s)
{
	int p1 = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (p1 = 0; s[p1] != '\0'; p1++)
	{
		if (s[p1] >= '0' && s[p1] <= '9')
		{
			result *= 10;
			result += (s[p1] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

