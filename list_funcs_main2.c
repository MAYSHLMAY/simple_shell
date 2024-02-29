#include "headers/Shell_Header.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first nde
 *
 * Return: size of list
 */
size_t list_len(const histo_t *h)
{
	size_t p1 = 0;

	while (h)
	{
		h = h->next;
		p1++;
	}
	return (p1);
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
	size_t p1 = list_len(head), p2;
	char **strs;
	char *c_r;

	if (!head || !p1)
		return (NULL);
	strs = malloc(sizeof(char *) * (p1 + 1));
	if (!strs)
		return (NULL);
	for (p1 = 0; nde; nde = nde->next, p1++)
	{
		c_r = malloc(my_strlen(nde->c_r) + 1);
		if (!c_r)
		{
			for (p2 = 0; p2 < p1; p2++)
				free(strs[p2]);
			free(strs);
			return (NULL);
		}

		c_r = my_strcpy(c_r, nde->c_r);
		strs[p1] = c_r;
	}
	strs[p1] = NULL;
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
	size_t p1 = 0;

	while (h)
	{
		my_puts(convert_number(h->num, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		my_puts(h->c_r ? h->c_r : "(nil)");
		my_puts("\n");
		h = h->next;
		p1++;
	}
	return (p1);
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
	char *par = NULL;

	while (nde)
	{
		par = starts_with(nde->c_r, prefix);
		if (par && ((c == -1) || (*par == c)))
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
	size_t p1 = 0;

	while (head)
	{
		if (head == nde)
			return (p1);
		head = head->next;
		p1++;
	}
	return (-1);
}
