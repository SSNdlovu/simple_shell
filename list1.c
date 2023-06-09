#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * list_len - computes the size of a linked list
 * @h: points to the first node
 * Return: returns the length of the list
 */
size_t list_len(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * list_to_strings -  generates an array of strings from the list->str
 * @head: points to the first node
 * Return: will return string arrays
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t ii = list_len(head), jj;
	char **strs;
	char *str;

	if (!head || !ii)
		return (NULL);
	strs = malloc(sizeof(char *) * (ii + 1));
	if (!strs)
		return (NULL);
	for (ii = 0; node; node = node->next, ii++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (jj = 0; jj < ii; jj++)
				free(strs[jj]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[ii] = str;
	}
	strs[ii] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a linked list_t list
 * @h: pointes to the first node
 * Return: will return the length of the list
 */
size_t print_list(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * node_starts_with - the node whose string begins with the specified prefix
 * @node: points to the head og the list
 * @prefix: the string to be matched
 * @c: the next character to match after the prefix
 * Return: returns the matched node or null if not found
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - obtains the index of a node
 * @head: points to head of the list
 * @node: points to the actual node
 * Return: the index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t ii = 0;

	while (head)
	{
		if (head == node)
			return (ii);
		head = head->next;
		ii++;
	}
	return (-1);
}
