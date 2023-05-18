#include "shell.h"

/**
 * _memset - populates memory with a specific byte value
 * @s: points to the memory area
 * @b: the byte used to fill *s
 * @n: the amount of bytes filled
 * Return: (s) the memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int ii;

	for (ii = 0; ii < n; ii++)
		s[ii] = b;
	return (s);
}

/**
 * ffree - deallocates a string array
 * @pp: string belonging to other strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous allocated block
 * @old_size: byte of previous block
 * @new_size: byte of new block
 * Return: a pointer to the old memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
