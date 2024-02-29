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
	int p1 = 0, p3 = 0;

	for (p3 = 0, p1 = start; p1 < stop; p1++)
		if (pathstr[p1] != ':')
		{
			buffer[p3++] = pathstr[p1];
			buffer[p3] = 0;
		}
	return (buffer);
}

/**
 * is_cmd - determines if a file is an executable command
 * @fm: pointer to the fm struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(flex_t *fm, char *path)
{
	struct stat file_stat;

	(void)fm;
	if (!path || stat(path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * find_path - finds the command's
 * @fm: pointer to the fm struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_path(flex_t *fm, char *pathstr, char *cmd)
{
	int p1 = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(fm, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[p1] || pathstr[p1] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, p1);
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			if (is_cmd(fm, path))
				return (path);
			if (!pathstr[p1])
				break;
			curr_pos = p1;
		}
		p1++;
	}
	return (NULL);
}
