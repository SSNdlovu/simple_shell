#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * is_cmd - the file will be checked if its an executable command
 * @info: the information structure
 * @path: the path used to the file
 * Return: 1 if it is a comand, 0 if not
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - characters are copied
 * @pathstr: the actual PATH of the string
 * @start: where index starts
 * @stop: where index ends
 * Return: a pointer to the fresh buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int ii = 0, kk = 0;

	for (kk = 0, ii = start; ii < stop; ii++)
		if (pathstr[ii] != ':')
			buf[kk++] = pathstr[ii];
	buf[kk] = 0;
	return (buf);
}

/**
 * find_path - searches for the specified command in the PATH string
 * @info: the structure of the information
 * @pathstr: the PATH of the string
 * @cmd: the command to be found
 * Return:  the full path of the command, or NULL otherwise
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int ii = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[ii] || pathstr[ii] == ':')
		{
			path = dup_chars(pathstr, curr_pos, ii);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[ii])
				break;
			curr_pos = ii;
		}
		ii++;
	}
	return (NULL);
}
