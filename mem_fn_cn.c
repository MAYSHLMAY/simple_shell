#include "headers/Shell_Header.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int p1;

	for (p1 = 0; p1 < n; p1++)
		s[p1] = b;
	return (s);
}

/**
 * free_string_array - frees a string array
 * @pp: string array to be freed
 */
void free_string_array(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * free_and_null - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous dynamically allocated block
 * @old_size: size of the previous block in bytes
 * @new_size: size of the new block in bytes
 *
 * Return: pointer to the reallocated block of memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *par;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	par = malloc(new_size);
	if (!par)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		par[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (par);
}

