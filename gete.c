#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * get_environ - retuur envi
 * @info: Strue contan
 *          connt fuion proype.
 * Return: Always nothing
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Rem an envir
 * @info: Struc conining potial arguts. Used 2 maint
 *        const funct protot.
 *  Return: pos on del, nothing other
 * @var: da stg envir vari prop
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t ii = 0;
	char *pp;

	if (!node || !var)
		return (0);

	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), ii);
			ii = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		ii++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initie a n
 *             or modan exing 1
 * @info: Struct cong poten argum. Used 2 maint
 *        const funct protot.
 * @var: da str enviro vari prope
 * @value: da str envro vari val
 *  Return: Always nothing
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *pp;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

