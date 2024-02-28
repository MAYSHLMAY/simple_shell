#include "headers/Shell_Header.h"

/**
 **my_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *my_strncat(char *dest, char *src, int n)
{
	char *ptr = dest;

	while (*ptr)
		ptr++;
	while (*src && n > 0)
	{
		*ptr = *src;
		ptr++;
		src++;
		n--;
	}
	*ptr = '\0';
	return (dest);
}

/**
 **my_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *my_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
*/

char *my_strdup(const char *str)
{
	int length = 0;
	const char *ptr = str;
	char *ret;
	char *dest;

	while (*ptr)
	{
		length++;
		ptr++;
	}

	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	ptr = str;
	dest = ret;
	while (*ptr)
	{
		*dest = *ptr;
		dest++;
		ptr++;
	}
	*dest = '\0';
	return (ret);
}

/**
 *my_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		my_putchar(str[i]);
		i++;
	}
}
