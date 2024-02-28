#include "headers/Shell_Header.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first nde
 *
 * Return: size of list
 */
size_t list_len(const histo_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->c_r
 * @head: pointer to first nde
 *
 * Return: array of strings
 */
char **list_to_strings(histo_t *head)
{
	histo_t *nde = head;
	size_t i = list_len(head), j;
	char **strs;
	char *c_r;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nde; nde = nde->next, i++)
	{
		c_r = malloc(my_strlen(nde->c_r) + 1);
		if (!c_r)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		c_r = my_strcpy(c_r, nde->c_r);
		strs[i] = c_r;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a histo_t linked list
 * @h: pointer to first nde
 *
 * Return: size of list
 */
size_t print_list(const histo_t *h)
{
	size_t i = 0;

	while (h)
	{
		my_puts(convert_number(h->num, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		my_puts(h->c_r ? h->c_r : "(nil)");
		my_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns nde whose string starts with prefix
 * @nde: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match nde or null
 */
histo_t *node_starts_with(histo_t *nde, char *prefix, char c)
{
	char *p = NULL;

	while (nde)
	{
		p = starts_with(nde->c_r, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (nde);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a nde
 * @head: pointer to list head
 * @nde: pointer to the nde
 *
 * Return: index of nde or -1
 */
ssize_t get_node_index(histo_t *head, histo_t *nde)
{
	size_t i = 0;

	while (head)
	{
		if (head == nde)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
