#include "shell.h"

/**
 * interactive - rtn positive int
 * @info: str addr
 *
 * Return: pos if inter, nothing if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - chcks char a delm
 * @c: charect to cck
 * @delim: delm str
 * Return: pos if checks out, nothing if doesnt
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - chcks alpha char
 * @c: char inp
 * Return: pos c is alpha, nothing if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - str to int
 * @s: str cnrtd
 * Return: nothing if num in str, cnvrtd num if not
 */

int _atoi(char *s)
{
	int ii, signn = 1, flagg = 0, outputt;
	unsigned int resultt = 0;

	for (ii = 0; s[ii] != '\0' && flagg != 2; ii++)
	{
		if (s[ii] == '-')
			signn *= -1;

		if (s[ii] >= '0' && s[ii] <= '9')
		{
			flagg = 1;
			resultt *= 10;
			resultt += (s[ii] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (signn == -1)
		outputt = -resultt;
	else
		outputt = resultt;

	return (outputt);
}

