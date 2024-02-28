#include "headers/Shell_Header.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @c_r: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *c_r, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (c_r == NULL || c_r[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; c_r[i] != '\0'; i++)
		if (!is_delimiter(c_r[i], d) && (is_delimiter(c_r[i + 1], d) || !c_r[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(c_r[i], d))
			i++;
		k = 0;
		while (!is_delimiter(c_r[i + k], d) && c_r[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = c_r[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}