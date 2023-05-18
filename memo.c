#include "shell.h"

/**
 * bfree - deallocates a pointer and sets the address to NULL.
 * @ptr: address of the pointer to deallocate.
 * Return: Returns 1 if deallocated successfully, otherwise returns 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
