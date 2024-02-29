#include "headers/Shell_Header.h"
/**
 * pr_erro - Prints an error message.
 * @fm: The parameter & return fm struct.
 * @estr: String containing specified error type.
 *
 * Return: Nothing.
 */
void pr_erro(flex_t *fm, char *estr)
{
	_error_puts(fm->fname);
	_error_puts(": ");
	pr_int(fm->line_count, STDERR_FILENO);
	_error_puts(": ");
	_error_puts(fm->arg_o_v[0]);
	_error_puts(": ");
	_error_puts(estr);
}

/**
 * pr_int - Function prints a decimal (integer) number (base 10).
 * @input: The input.
 * @file_d: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int pr_int(int input, int file_d)
{
	int (*__putchar)(char) = my_putchar;
	int p1, count = 0;
	unsigned int _abs_, current;

	if (file_d == STDERR_FILENO)
		__putchar = my_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p1 = 1000000000; p1 > 1; p1 /= 10)
	{
		if (_abs_ / p1)
		{
			__putchar('0' + current / p1);
			count++;
		}
		current %= p1;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converter function, a clone of itoa.
 * @number: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: String.
 */
char *convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = number;

	if (!(flags & C_US) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = flags & C_LC ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do {
		*--pointer = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * remove_comments - Function replaces the first instance of '#' with '\0'.
 * @buffer: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments(char *buffer)
{
	int p1;

	for (p1 = 0; buffer[p1] != '\0'; p1++)
		if (buffer[p1] == '#' && (!p1 || buffer[p1 - 1] == ' '))
		{
			buffer[p1] = '\0';
			break;
		}
}
