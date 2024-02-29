#include "headers/Shell_Header.h"

/**
 *intu - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int intu(char *s)
{
	int sign = 1, flag = 0, output, p1 = 0;
	unsigned int result = 0;

	while (s[p1] != '\0' && flag != 2)
	{
		if (s[p1] == '-')
			sign *= -1;

		if (s[p1] >= '0' && s[p1] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[p1] - '0');
		}
		else if (flag == 1)
			flag = 2;

		p1++;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * ch_del - checks if character
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int ch_del(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * chec - test if current char
 * @fm: the parameter struct
 * @buf: the char buffer
 * @par: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chec(flex_t *fm, char *buf, size_t *par)
{
	size_t p2 = *par;
	int ret = 0;

	switch (buf[p2])
	{
		case '|':
			if (buf[p2 + 1] == '|')
			{
				buf[p2] = 0;
				p2++;
				fm->cmd_buf_type = C_OR;
				ret = 1;
			}
			break;
		case '&':
			if (buf[p2 + 1] == '&')
			{
				buf[p2] = 0;
				p2++;
				fm->cmd_buf_type = C_AND;
				ret = 1;
			}
			break;
		case ';':
			buf[p2] = 0;
			fm->cmd_buf_type = C_C_N;
			ret = 1;
			break;
		default:
			ret = 0;
			break;
	}

	*par = p2;
	return (ret);
}

