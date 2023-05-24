#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * _strcpy - a string will be copied
 * @dest: the destination of the string
 * @src: the source of te string
 * Return: destination pointer is returned
 */
char *_strcpy(char *dest, char *src)
{
	int ii = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[ii])
	{
		dest[ii] = src[ii];
		ii++;
	}
	dest[ii] = 0;
	return (dest);
}

/**
 * _strdup - a string will be duplicated
 * @str: the duplicated string
 * Return: the duplicated string pointer to be returned
 */
char *_strdup(const char *str)
{
	int leng = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leng++;
	ret = malloc(sizeof(char) * (leng + 1));
	if (!ret)
		return (NULL);
	for (leng++; leng--;)
		ret[leng] = *--str;
	return (ret);
}

/**
 * _puts - an input string is printed
 * @str: the printed string
 * Return: None
 */
void _puts(char *str)
{
	int ii = 0;

	if (!str)
		return;
	while (str[ii] != '\0')
	{
		_putchar(str[ii]);
		ii++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: if successful 1.
 * if there is an  error, -1 is returned, and errno is set.
 */
int _putchar(char c)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(1, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}
