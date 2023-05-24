#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * get_history_file - retrieves the history file
 * @info: struct of parameters
 * Return: a dynamically allocated string containing the history file
*/

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - generates a new file or appends to an existing file.
 * @info: the struct containing parameters.
 * Return: Returns 1 if successful, otherwise returns -1.
*/
int write_history(info_t *info)
{
	ssize_t ffd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	ffd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (ffd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, ffd);
		_putfd('\n', ffd);
	}
	_putfd(BUF_FLUSH, ffd);
	close(ffd);
	return (1);
}

/**
 * read_history - retrieves history from a file
 * @info: the struct containing parameters
 * Return: Returns histcount if successful, otherwise returns 0.
 */
int read_history(info_t *info)
{
	int ii, last = 0, linecount = 0;
	ssize_t ffd, rrdlen, ffsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	ffd = open(filename, O_RDONLY);
	free(filename);
	if (ffd == -1)
		return (0);
	if (!fstat(ffd, &st))
		ffsize = st.st_size;
	if (ffsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (ffsize + 1));
	if (!buf)
		return (0);
	rrdlen = read(ffd, buf, ffsize);
	buf[ffsize] = 0;
	if (rrdlen <= 0)
		return (free(buf), 0);
	close(ffd);
	for (ii = 0; ii < ffsize; ii++)
		if (buf[ii] == '\n')
		{
			buf[ii] = 0;
			build_history_list(info, buf + last, linecount++);
			last = ii + 1;
		}
	if (last != ii)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - appends a new entry to linked list from the history
 * @info: A structure containing the necessary arguments, for maintenance.
 * @buf: The buffer to be added.
 * @linecount: The count of lines in the history, also known as histcount.
 * Return: Always returns 0.
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - This function updates the history linked list numbers
 * @info: A data structure that holds the arguments. It is utilized to preserve
 * Return: the updated histcount value
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int ii = 0;

	while (node)
	{
		node->num = ii++;
		node = node->next;
	}
	return (info->histcount = ii);
}
