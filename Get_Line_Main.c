#include "Shell_Header.h"

/**
 * input_buffer - Buffers chained commands
 * @info: The parameter struct
 * @buf: Address of buffer
 * @len: Address of len var
 *
 * Return: The number of bytes read.
 */
ssize_t input_buffer(information_t *info, char **buf, size_t *len)
{
	ssize_t read_result = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*free_and_null((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read_result = getline(buf, &len_p, stdin);
#else
		read_result = _getline(info, buf, &len_p);
#endif
		if (read_result > 0)
		{
			if ((*buf)[read_result - 1] == '\n')
			{
				(*buf)[read_result - 1] = '\0'; /* Remove trailing newline */
				read_result--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (my_strchr(*buf, ';')) is this a command chain? */
			{
				*len = read_result;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_result);
}

/**
 * get_input - Gets a line minus the newline
 * @info: The parameter struct
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(information_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t buffer_index, j, buffer_length;
	ssize_t read_result = 0;
	char **buf_p = &(info->arg), *p;

	my_putchar(BUF_FLUSH);
	read_result = input_buffer(info, &buf, &buffer_length);
	if (read_result == -1) /* EOF */
		return (-1);
	if (buffer_length)	/* We have commands left in the chain buffer */
	{
		j = buffer_index; /* Init new iterator to current buffer position */
		p = buf + buffer_index; /* Get pointer for return */

		check_chain(info, buf, &j, buffer_index, buffer_length);
		while (j < buffer_length) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		buffer_index = j + 1; /* Increment past nulled ';' */
		if (buffer_index >= buffer_length) /* Reached end of buffer? */
		{
			buffer_index = buffer_length = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (my_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
	return (read_result); /* Return length of buffer from _getline() */
}

/**
 * read_buffer - Reads a buffer
 * @info: The parameter struct
 * @buf: Buffer
 * @index: Size
 *
 * Return: The number of bytes read.
 */
ssize_t read_buffer(information_t *info, char *buffer, size_t *index)
{
	ssize_t read_result = 0;

	if (*index)
		return (0);
	read_result = read(info->readfd, buffer, READ_BUF_SIZE);
	if (read_result >= 0)
		*index = read_result;
	return (read_result);
}

/**
 * _getline - Retrieves the next line of input from STDIN
 * @info: The parameter struct
 * @line_ptr: Address of pointer to buffer, preallocated or NULL
 * @line_length: Size of preallocated line_ptr buffer if not NULL
 *
 * Return: The number of characters read on success, or -1 on failure.
 */


 int _getline(information_t *info, char **line_ptr, size_t *line_length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buffer_index, buffer_length;
	size_t line_index;
	ssize_t read_result = 0, search_result = 0;
	char *line = NULL, *new_line = NULL, *newline_character;

	line = *line_ptr;
	if (line && line_length)
		search_result = *line_length;
	if (buffer_index == buffer_length)
		buffer_index = buffer_length = 0;

	read_result = read_buffer(info, buffer, &buffer_length);
	if (read_result == -1 || (read_result == 0 && buffer_length == 0))
		return (-1);

	newline_character = my_strchr(buffer + buffer_index, '\n');
	line_index = newline_character ? 1 + (unsigned int)(newline_character - buffer) : buffer_length;
	new_line = _realloc(line, search_result, search_result ? search_result + line_index : line_index + 1);
	if (!new_line)
		return (line ? free(line), -1 : -1);

	if (search_result)
		my_strncat(new_line, buffer + buffer_index, line_index - buffer_index);
	else
		my_strncpy(new_line, buffer + buffer_index, line_index - buffer_index + 1);

	search_result += line_index - buffer_index;
	buffer_index = line_index;
	line = new_line;

	if (line_length)
		*line_length = search_result;
	*line_ptr = line;
	return (search_result);
}

 /**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	my_puts("\n");
	my_puts("$ ");
	my_putchar(BUF_FLUSH);
}




