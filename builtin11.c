#include "shell.h"

/**
 * _myhistory - dis da hist ls, 1 comm by line, flollowed
 *              with ln num, start @ nothing.
 * @info: Struc cont poten arg. U 2 maint
 *        const func proto.
 *  Return: Always nothing
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - ali 2 str
 * @info: para str
 * @str: da str ali
 *
 * Return: nothing on pass, pos on failure
 */
int unset_alias(info_t *info, char *str)
{
	char *pp, cc;
	int rett;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	cc = *pp;
	*pp = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pp = cc;
	return (rett);
}

/**
 * set_alias - ali 2 str
 * @info: param str
 * @str: da str ali
 *
 * Return: Always nothing pass, pos fail
 */
int set_alias(info_t *info, char *str)
{
	char *pp;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print ali str
 * @node: da ali nd
 *
 * Return: Always nothing pass, pos on fail
 */
int print_alias(list_t *node)
{
	char *pp = NULL, *aa = NULL;

	if (node)
	{
		pp = _strchr(node->str, '=');
		for (aa = node->str; aa <= pp; aa++)
		_putchar(*aa);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - copies da alia
 * @info: Struct contai poten arg. 2 maint
 *          const funcn proto.
 *  Return: Always nothing
 */
int _myalias(info_t *info)
{
	int ii = 0;
	char *pp = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (ii = 1; info->argv[ii]; ii++)
	{
		pp = _strchr(info->argv[ii], '=');
		if (pp)
			set_alias(info, info->argv[ii]);
		else
			print_alias(node_starts_with(info->alias, info->argv[ii], '='));
	}

	return (0);
}

