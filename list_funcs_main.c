#include "headers/Shell_Header.h"

/**
 * add_node - adds a nde to the start of the list
 * @head: address of pointer to head nde
 * @c_r: c_r field of nde
 * @num: nde index used by history
 *
 * Return: size of list
 */
histo_t *add_node(histo_t **head, const char *c_r, int num)
{
	histo_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(histo_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(histo_t));
	new_head->num = num;
	if (c_r)
	{
		new_head->c_r = my_strdup(c_r);
		if (!new_head->c_r)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a nde to the end of the list
 * @head: address of pointer to head nde
 * @c_r: c_r field of nde
 * @num: nde index used by history
 *
 * Return: size of list
 */
histo_t *add_node_end(histo_t **head, const char *c_r, int num)
{
	histo_t *new_node, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_node = malloc(sizeof(histo_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(histo_t));
	new_node->num = num;
	if (c_r)
	{
		new_node->c_r = my_strdup(c_r);
		if (!new_node->c_r)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the c_r element of a histo_t linked list
 * @h: pointer to first nde
 *
 * Return: size of list
 */
size_t print_list_str(const histo_t *h)
{
	size_t p1 = 0;

	while (h)
	{
		my_puts(h->c_r ? h->c_r : "(nil)");
		my_puts("\n");
		h = h->next;
		p1++;
	}
	return (p1);
}

/**
 * delete_node_at_index - deletes nde at given index
 * @head: address of pointer to first nde
 * @index: index of nde to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(histo_t **head, unsigned int index)
{
	histo_t *nde, *prev_node;
	unsigned int p1 = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nde = *head;
		*head = (*head)->next;
		free(nde->c_r);
		free(nde);
		return (1);
	}
	nde = *head;
	while (nde)
	{
		if (p1 == index)
		{
			prev_node->next = nde->next;
			free(nde->c_r);
			free(nde);
			return (1);
		}
		p1++;
		prev_node = nde;
		nde = nde->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head nde
 *
 * Return: void
 */
void free_list(histo_t **head_ptr)
{
	histo_t *nde, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nde = head;
	while (nde)
	{
		next_node = nde->next;
		free(nde->c_r);
		free(nde);
		nde = next_node;
	}
	*head_ptr = NULL;
}
