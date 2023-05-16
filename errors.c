#include "shell.h"

/**
 * _eputs - pri inp str
 * @str: da str 2 print
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int ii = 0;

	if (!str)
		return;
	while (str[ii] != '\0')
	{
		_eputchar(str[ii]);
		ii++;
	}
}

/**
 * _eputchar - writes da char 2 std
 * @c: da char to pri
 *
 * Return: On pass pos.
 * On fail, -neg is retur, and err set appropr.
 */
int _eputchar(char c)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(2, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}

/**
 * _putfd - writ da char c 2 giv fud
 * @c: da char 2 pri
 * @fd: da filedescri 2 wri 2
 *
 * Return: On pass pos.
 * On fail, -neg is re, and err set appro.
 */
int _putfd(char c, int fd)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(fd, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}

/**
 * _putsfd - print an inp str
 * @str: da str 2 be prin
 * @fd: tda filedes to write to
 *
 * Return: da num char puttt
 */
int _putsfd(char *str, int fd)
{
	int ii = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ii += _putfd(*str++, fd);
	}
	return (ii);
}

