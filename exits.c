#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 **_strncpy - copy str
 *@dest: da dest str to copy 2
 *@src: da source str
 *@n: da amnt of char to copy
 *Return: da concate str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int ii, jj;
	char *z = dest;

	ii = 0;
	while (src[ii] != '\0' && ii < n - 1)
	{
		dest[ii] = src[ii];
		ii++;
	}
	if (ii < n)
	{
		jj = ii;
		while (jj < n)
		{
			dest[jj] = '\0';
			jj++;
		}
	}
	return (z);
}

/**
 **_strncat - concate 2 str
 *@dest: 1st str
 *@src: 2nd str
 *@n: da amnt of byte to all usd
 *Return: da concate str
 */
char *_strncat(char *dest, char *src, int n)
{
	int ii, jj;
	char *z = dest;

	ii = 0;
	jj = 0;
	while (dest[ii] != '\0')
		ii++;
	while (src[jj] != '\0' && jj < n)
	{
		dest[ii] = src[jj];
		ii++;
		jj++;
	}
	if (jj < n)
		dest[ii] = '\0';
	return (z);
}

/**
 **_strchr - locate str
 *@s: str  parse
 *@c: char to find
 *Return: (z) point to z
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

