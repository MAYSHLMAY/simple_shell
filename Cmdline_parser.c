#include "headers/Shell_Header.h"

/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to the new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
		{
			buffer[k++] = pathstr[i];
			buffer[k] = 0;
		}
	return (buffer);
}

/**
 * is_cmd - determines if a file is an executable command
 * @form: pointer to the form struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(form_t *form, char *path)
{
	struct stat file_stat;

	(void)form;
	if (!path || stat(path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * find_path - finds the command's full path in the PATH string
 * @form: pointer to the form struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_path(form_t *form, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(form, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			if (is_cmd(form, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
