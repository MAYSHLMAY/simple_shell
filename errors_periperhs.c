#include "Shell_Header.h"

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
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
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
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
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

/**
 * print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing specified error type.
 *
 * Return: Nothing.
 */
void print_error(information_t *info, char *estr)
{
	_error_puts(info->fname);
	_error_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_error_puts(": ");
	_error_puts(info->argv[0]);
	_error_puts(": ");
	_error_puts(estr);
}

/**
 * print_decimal - Function prints a decimal (integer) number (base 10).
 * @input: The input.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_decimal(int input, int file_descriptor)
{
	int (*__putchar)(char) = my_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_descriptor == STDERR_FILENO)
		__putchar = _error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
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
	unsigned long n =number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
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
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}