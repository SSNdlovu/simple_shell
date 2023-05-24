#include "shell.h"

/**
 * **strtow - seperates a string into words. ignore repeated delimiters
 * @str: the string that is an input
 * @d: the string delimeter
 * Return: pointer of an array, or NULL if failed
 */

char **strtow(char *str, char *d)
{
	int ii, jj, kk, mm, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (ii = 0; str[ii] != '\0'; ii++)
		if (!is_delim(str[ii], d) && (is_delim(str[ii + 1], d) || !str[ii + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (is_delim(str[ii], d))
			ii++;
		kk = 0;
		while (!is_delim(str[ii + kk], d) && str[ii + kk])
			kk++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!s[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			s[jj][mm] = str[ii++];
		s[jj][mm] = 0;
	}
	s[jj] = NULL;
	return (s);
}

/**
 * **strtow2 - seperates a string into words
 * @str: the string that is an input
 * @d: the actual string delimeter
 * Return: pointer to an array, or NULL if failed
 */
char **strtow2(char *str, char d)
{
	int ii, jj, kk, mm, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (ii = 0; str[ii] != '\0'; ii++)
		if ((str[ii] != d && str[ii + 1] == d) ||
				    (str[ii] != d && !str[ii + 1]) || str[ii + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (str[ii] == d && str[ii] != d)
			ii++;
		kk = 0;
		while (str[ii + kk] != d && str[ii + kk] && str[ii + kk] != d)
			kk++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!s[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			s[jj][mm] = str[ii++];
		s[jj][mm] = 0;
	}
	s[jj] = NULL;
	return (s);
}
