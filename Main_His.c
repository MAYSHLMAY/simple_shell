#include "headers/Shell_Header.h"

/**
 * get_history_file - gets the history file
 * @fm: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(flex_t *fm)
{
	char *buf, *dir;

	dir = my_gev(fm, "HOME=");
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
 * @fm: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(flex_t *fm)
{
	ssize_t fd;
	char *filename = get_history_file(fm);
	histo_t *nde = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nde = fm->history; nde; nde = nde->next)
	{
		_puts_filed(nde->c_r, fd);
		_putfile_d('\n', fd);
	}
	_putfile_d(B_F, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @fm: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(flex_t *fm)
{
	int p1, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(fm);

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
	for (p1 = 0; p1 < fsize; p1++)
		if (buf[p1] == '\n')
		{
			buf[p1] = 0;
			build_history_list(fm, buf + last, linecount++);
			last = p1 + 1;
		}
	if (last != p1)
		build_history_list(fm, buf + last, linecount++);
	free(buf);
	fm->histcount = linecount;
	while (fm->histcount-- >= H_MAX)
		delete_node_at_index(&(fm->history), 0);
	renumber_history(fm);
	return (fm->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @fm: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(flex_t *fm, char *buf, int linecount)
{
	histo_t *nde = NULL;

	if (fm->history)
		nde = fm->history;
	add_node_end(&nde, buf, linecount);

	if (!fm->history)
		fm->history = nde;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @fm: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(flex_t *fm)
{
	histo_t *nde = fm->history;
	int p1 = 0;

	while (nde)
	{
		nde->num = p1++;
		nde = nde->next;
	}
	return (fm->histcount = p1);
}
