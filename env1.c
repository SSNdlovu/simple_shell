#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * _myenv - pr da curr envir
 * @info: Struct cont pote argum. 2 maint
 *          constt funct proto.
 * Return: Always nothing
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - get da val an envir var
 * @info: Struct contai potent argume. 2 maint
 * @name: envie vari names
 *
 * Return: da val
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pp;

	while (node)
	{
		pp = starts_with(node->str, name);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initi fresh environ vari,
 *             mod an old 1
 * @info: Struct contain potent argum. 2 maint
 *        const funct proto.
 *  Return: Always nothing
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remm enviro vari
 * @info: Struc conta poten argum. 2 main
 *        connt fun protot.
 * Return: Always nothing
 */
int _myunsetenv(info_t *info)
{
	int ii;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (ii = 1; ii <= info->argc; ii++)
		_unsetenv(info, info->argv[ii]);

	return (0);
}

/**
 * populate_env_list - popus e
 * @info: Struc coning pote argu. 2 maint
 *          const func proto.
 * Return: Always nothing
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t ii;

	for (ii = 0; environ[ii]; ii++)
		add_node_end(&node, environ[ii], 0);
	info->env = node;
	return (0);
}

