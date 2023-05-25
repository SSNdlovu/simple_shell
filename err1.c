#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * _erratoi - conv a str int
 * @s: da str to be conve
 * Return: nothing num in str, conv num otherw
 *       -neg on fail
 */
int _erratoi(char *s)
{
	int ii = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (ii = 0;  s[ii] != '\0'; ii++)
	{
		if (s[ii] >= '0' && s[ii] <= '9')
		{
			result *= 10;
			result += (s[ii] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - print fail mess
 * @info: da para & ret info str
 * @estr: str contain speci fail type
 * Return: nothing if no num str, conver num otherw
 *        -neg on fail
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - func print a dec
 * @input: da inp
 * @fd: da filedescri
 *
 * Return: num char print
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int ii, countt = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		countt++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (ii = 1000000000; ii > 1; ii /= 10)
	{
		if (_abs_ / ii)
		{
			__putchar('0' + current / ii);
			countt++;
		}
		current %= ii;
	}
	__putchar('0' + current);
	countt++;

	return (countt);
}

/**
 * convert_number - conver func
 * @num: num
 * @base: basse
 * @flags: arg fl
 *
 * Return: str
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arrayy;
	static char bufferr[50];
	char signn = 0;
	char *ptrr;
	unsigned long nn = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		nn = -num;
		signn = '-';

	}
	arrayy = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrr = &bufferr[49];
	*ptrr = '\0';

	do	{
		*--ptrr = arrayy[nn % base];
		nn /= base;
	} while (nn != 0);

	if (signn)
		*--ptrr = signn;
	return (ptrr);
}

/**
 * remove_comments - funct replace 1st
 * @buf: addr of da str 2 mod
 *
 * Return: Always nothing;
 */
void remove_comments(char *buf)
{
	int ii;

	for (ii = 0; buf[ii] != '\0'; ii++)
		if (buf[ii] == '#' && (!ii || buf[ii - 1] == ' '))
		{
			buf[ii] = '\0';
			break;
		}
}

