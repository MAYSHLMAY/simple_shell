#include "headers/Shell_Header.h"

/**
 * get_history_file - gets the history file
 * @form: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(form_t *form)
{
	char *buf, *dir;

	dir = _getenv(form, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(H_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	my_strcpy(buf, dir);
	my_strcat(buf, "/");
	my_strcat(buf, H_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @form: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(form_t *form)
{
	ssize_t fd;
	char *filename = get_history_file(form);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = form->history; node; node = node->next)
	{
		_puts_filed(node->str, fd);
		_putfile_d('\n', fd);
	}
	_putfile_d(B_F, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @form: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(form_t *form)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(form);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(form, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(form, buf + last, linecount++);
	free(buf);
	form->histcount = linecount;
	while (form->histcount-- >= H_MAX)
		delete_node_at_index(&(form->history), 0);
	renumber_history(form);
	return (form->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @form: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(form_t *form, char *buf, int linecount)
{
	list_t *node = NULL;

	if (form->history)
		node = form->history;
	add_node_end(&node, buf, linecount);

	if (!form->history)
		form->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @form: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(form_t *form)
{
	list_t *node = form->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (form->histcount = i);
}
