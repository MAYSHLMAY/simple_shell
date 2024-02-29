#include "headers/Shell_Header.h"

/**
 * input_buffer - Buffers chained commands
 * @fm: The parameter struct
 * @buf: Address of buffer
 * @lenz: Address of lenz var
 *
 * Return: The number of bytes read.
 */
ssize_t input_buffer(flex_t *fm, char **buf, size_t *lenz)
{
	ssize_t re_ra = 0;
	size_t len_p = 0;

	if (!*lenz) /* If nothing left in the buffer, fill it */
	{
		/*free_and_null((void **)fm->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, c_block);
#if UGL
		re_ra = getline(buf, &len_p, stdin);
#else
		re_ra = _getline(fm, buf, &len_p);
#endif
		if (re_ra > 0)
		{
			if ((*buf)[re_ra - 1] == '\n')
			{
				(*buf)[re_ra - 1] = '\0';
				re_ra--;
			}
			fm->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(fm, *buf, fm->histcount++);
			{
				*lenz = re_ra;
				fm->cmd_buf = buf;
			}
		}
	}
	return (re_ra);
}

/**
 * get_input - Gets a line minus the newline
 * @fm: The parameter struct
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(flex_t *fm)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t buf_idx, p2, buf_len;
	ssize_t re_ra = 0;
	char **buf_p = &(fm->arg), *par;

	my_putchar(B_F);
	re_ra = input_buffer(fm, &buf, &buf_len);
	if (re_ra == -1) /* EOF */
		return (-1);
	if (buf_len)	/* We have commands left in the chain buffer */
	{
		p2 = buf_idx; /* Init new iterator to current buffer position */
		par = buf + buf_idx; /* Get pointer for return */

		check_chain(fm, buf, &p2, buf_idx, buf_len);
		while (p2 < buf_len) /* Iterate to semicolon or end */
		{
			if (chec(fm, buf, &p2))
				break;
			p2++;
		}

		buf_idx = p2 + 1; /* Increment past nulled ';' */
		if (buf_idx >= buf_len) /* Reached end of buffer? */
		{
			buf_idx = buf_len = 0; /* Reset position and length */
			fm->cmd_buf_type = C_N;
		}

		*buf_p = par; /* Pass back pointer to current command position */
		return (my_strlen(par)); /* Return length of current command */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
	return (re_ra); /* Return length of buffer from _getline() */
}

/**
 * read_buffer - Reads a buffer
 * @fm: The parameter struct
 * @buffer: Buffer
 * @index: Size
 *
 * Return: The number of bytes read.
 */
ssize_t read_buffer(flex_t *fm, char *buffer, size_t *index)
{
	ssize_t re_ra = 0;

	if (*index)
		return (0);
	re_ra = read(fm->readfd, buffer, RU_B_S);
	if (re_ra >= 0)
		*index = re_ra;
	return (re_ra);
}

/**
 * _getline - Retrieves the next line of input from STDIN
 * @fm: The parameter struct
 * @line_ptr: Address of pointer to buffer, preallocated or NULL
 * @li_len: Size of preallocated line_ptr buffer if not NULL
 *
 * Return: The number of characters read on success, or -1 on failure.
 */


int _getline(flex_t *fm, char **line_ptr, size_t *li_len)
{
	static char buffer[RU_B_S];
	static size_t buf_idx, buf_len;
	size_t l_idx;
	ssize_t re_ra = 0, se_res = 0;
	char *line = NULL, *new_line = NULL, *n_char;

	line = *line_ptr;
	if (line && li_len)
		se_res = *li_len;
	if (buf_idx == buf_len)
		buf_idx = buf_len = 0;

	re_ra = read_buffer(fm, buffer, &buf_len);
	if (re_ra == -1 || (re_ra == 0 && buf_len == 0))
		return (-1);

	n_char = my_strchr(buffer + buf_idx, '\n');
	l_idx = n_char ? 1 + (unsigned int)(n_char - buffer) : buf_len;
	new_line = _realloc(line, se_res, se_res ? se_res + l_idx : l_idx + 1);
	if (!new_line)
		return (line ? free(line), -1 : -1);

	if (se_res)
		my_strncat(new_line, buffer + buf_idx, l_idx - buf_idx);
	else
		my_strncpy(new_line, buffer + buf_idx, l_idx - buf_idx + 1);

	se_res += l_idx - buf_idx;
	buf_idx = l_idx;
	line = new_line;

	if (li_len)
		*li_len = se_res;
	*line_ptr = line;
	return (se_res);
}

/**
 * c_block - a function blocks ctrl-C
 * @sig_num: the signal number ( May not used Intentionally )
 *
 * Return: void
*/
void c_block(__attribute__((unused))int sig_num)
{
	my_puts("\n");
	my_puts("$ ");
	my_putchar(B_F);
}




