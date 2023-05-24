#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * _strlen - the length of a string
 * @s: the string to be check
 * Return: number length of string to be returned
 */
int _strlen(char *s)
{
	int ii = 0;

	if (!s)
		return (0);

	while (*s++)
		ii++;
	return (ii);
}

/**
 * _strcmp - a sequal comparison of two strings is performed.
 * @s1: the initial string
 * @s2: the next string
 * Return: negative if s1 is less than s2,
 *	positive if s1 is more than s2,
 *	and zero if s1 equal s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - the needle is varified if it starts with haystack
 * @haystack: string to be searched
 * @needle: substring to be found
 * Return: returns next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - two strings are joined together
 * @dest: the destination  of the buffer
 * @src: the source of the buffer
 * Return: destination buffer will be returned
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
