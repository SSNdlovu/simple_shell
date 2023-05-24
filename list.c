#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * add_node - inserts a node at the beginning of the list
 * @head: the head node pointer is addressed
 * @str: string field of the node
 * @num: node index used for history
 * Return: returns the length of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - a node at the end of the list is inserted
 * @head: the head node pointer is addressed
 * @str: string field of the node
 * @num: node index used forhistory
 * Return: returns the length of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - the string element of a list_t will be printed
 * @h: points to the first node
 * Return: will return the length of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * delete_node_at_index - node at given index is to be deleted
 * @head: the first node pointer to be addressed
 * @index: the index of node to be delete
 * Return: 1 if successful, 0 if failed
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int ii = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (ii == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		ii++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - all nodes of a list are deallocated
 * @head_ptr: the head node pointer to be addressed
 * Return: None
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
