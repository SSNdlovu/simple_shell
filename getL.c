#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * input_buf - buff to chain comm
 * @info: para str
 * @buf: addr buff
 * @len: addr of lenght varia
 *
 * Return: bits readed
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rr = 0;
	size_t len_pp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rr = getline(buf, &len_pp, stdin);
#else
		rr = _getline(info, buf, &len_pp);
#endif
		if (rr > 0)
		{
			if ((*buf)[rr - 1] == '\n')
			{
				(*buf)[rr - 1] = '\0'; /* remove trailing newline */
				rr--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rr;
				info->cmd_buf = buf;
			}
		}
	}
	return (rr);
}

/**
 * get_input - get a ln - da newln
 * @info: param str
 *
 * Return: its readed
 */
ssize_t get_input(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t ii, jj, lenn;
	ssize_t rr = 0;
	char **buf_p = &(info->arg), *pp;

	_putchar(BUF_FLUSH);
	rr = input_buf(info, &buff, &lenn);
	if (rr == -1) /* EOF */
		return (-1);
	if (lenn) /* we have commands left in the chain buffer */
	{
		jj = ii; /* init new iterator to current buf position */
		pp = buff + ii; /* get pointer for return */

		check_chain(info, buff, &jj, ii, lenn);
		while (jj < lenn) /* iterate to semicolon or end */
		{
			if (is_chain(info, buff, &jj))
				break;
			jj++;
		}

		ii = jj + 1; /* increment past nulled ';'' */
		if (ii >= lenn) /* reached end of buffer? */
		{
			ii = lenn = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pp; /* pass back pointer to current command position */
		return (_strlen(pp)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (rr); /* return length of buffer from _getline() */
}

/**
 * read_buf - read buff
 * @info: para str
 * @buf: buff
 * @i: sizeer
 *
 * Return: rr
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	rr = read(info->readfd, buf, READ_BUF_SIZE);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getline - get da nex ln
 * @info: param str
 * @ptr: addr of point 2 buff, preallo or nada
 * @length: sized buff not nada
 *
 * Return: ss
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t ii, lenn;
	size_t kk;
	ssize_t rr = 0, ss = 0;
	char *pp = NULL, *new_pp = NULL, *cc;

	pp = *ptr;
	if (pp && length)
		ss = *length;
	if (ii == lenn)
		ii = lenn = 0;

	rr = read_buf(info, buf, &lenn);
	if (rr == -1 || (rr == 0 && lenn == 0))
		return (-1);

	cc = _strchr(buf + ii, '\n');
	kk = cc ? 1 + (unsigned int)(cc - buf) : lenn;
	new_pp = _realloc(pp, ss, ss ? ss + kk : kk + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (ss)
		_strncat(new_pp, buf + ii, kk - ii);
	else
		_strncpy(new_pp, buf + ii, kk - ii + 1);

	ss += kk - ii;
	ii = kk;
	pp = new_pp;

	if (length)
		*length = ss;
	*ptr = pp;
	return (ss);
}

/**
 * sigintHandler - block copying
 * @sig_num: da sig num
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

