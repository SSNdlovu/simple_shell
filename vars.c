#include "shell.h"

/**
 * is_chain - current character in buffer is tested if its a chain delimeter
 * @info: struct of the parameter
 * @buf: the buffer character
 * @p: current position within buf
 * Return: 1 when its a chain delimeter, 0 if not
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t jj = *p;

	if (buf[jj] == '|' && buf[jj + 1] == '|')
	{
		buf[jj] = 0;
		jj++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[jj] == '&' && buf[jj + 1] == '&')
	{
		buf[jj] = 0;
		jj++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[jj] == ';') /* found at the end */
	{
		buf[jj] = 0; /* semicolon replaced with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = jj;
	return (1);
}

/**
 * check_chain - checks to continue chaining using the last status
 * @info: the struct of the parameter
 * @buf: the character of the buffer
 * @p: the current position in buf is addressed
 * @i: the buf starting position
 * @len: the buf length
 * Return: None
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jj = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			jj = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			jj = len;
		}
	}

	*p = jj;
}

/**
 * replace_alias - substitute an aliases within the tokenized string
 * @info: struct of the parameter
 * Return: 1 when replaced, 0 if not
 */
int replace_alias(info_t *info)
{
	int ii;
	list_t *node;
	char *p;

	for (ii = 0; ii < 10; ii++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - substitutes vars within the tokenized string
 * @info: struct of the parameter
 * Return: 1 when replaced, 0 if not
 */
int replace_vars(info_t *info)
{
	int ii = 0;
	list_t *node;

	for (ii = 0; info->argv[ii]; ii++)
	{
		if (info->argv[ii][0] != '$' || !info->argv[ii][1])
			continue;

		if (!_strcmp(info->argv[ii], "$?"))
		{
			replace_string(&(info->argv[ii]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[ii], "$$"))
		{
			replace_string(&(info->argv[ii]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[ii][1], '=');
		if (node)
		{
			replace_string(&(info->argv[ii]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[ii], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - used to substitute a string
 * @old: old string is addressed
 * @new: new string is addressed
 * Return: 1 when replaced, 0 if not
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
