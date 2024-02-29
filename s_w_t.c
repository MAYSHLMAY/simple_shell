#include "headers/Shell_Header.h"

/**
 * **my_spx - splits a string into words.
 * @c_r: the input string
 * @z: the delimeter string
 * Return: a pointer
 */

char **my_spx(char *c_r, char *z)
{
	int p1, p2, p3, p4, nw = 0;
	char **s;

	if (c_r == NULL || c_r[0] == 0)
		return (NULL);
	if (!z)
		z = " ";
	for (p1 = 0; c_r[p1] != '\0'; p1++)
		if (!ch_del(c_r[p1], z) && (ch_del(c_r[p1 + 1], z) || !c_r[p1 + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p1 = 0, p2 = 0; p2 < nw; p2++)
	{
		while (ch_del(c_r[p1], z))
			p1++;
		p3 = 0;
		while (!ch_del(c_r[p1 + p3], z) && c_r[p1 + p3])
			p3++;
		s[p2] = malloc((p3 + 1) * sizeof(char));
		if (!s[p2])
		{
			for (p3 = 0; p3 < p2; p3++)
				free(s[p3]);
			free(s);
			return (NULL);
		}
		for (p4 = 0; p4 < p3; p4++)
			s[p2][p4] = c_r[p1++];
		s[p2][p4] = 0;
	}
	s[p2] = NULL;
	return (s);
}
