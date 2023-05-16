#include "shell.h"

/**
 * _myexit - goes out of shell
 * @info: Str with pot arg. To maintain
 * const fun proto.
 * Return: goes out from goutgoining status
 * (nothing) if info.argv[nothing] != "out"
 */
int _myexit(info_t *info)
{
	int exitcheckk;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheckk = _erratoi(info->argv[1]);
		if (exitcheckk == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - chng da curr dir the proc
 * @info: Str cont pot arg. To maint
 * const funct proto.
 * Return: Always nothing
 */
int _mycd(info_t *info)
{
	char *ss, *dirr, buffer[1024];
	int chdir_ret;

	ss = getcwd(buffer, 1024);
	if (!ss)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirr = _getenv(info, "HOME=");
		if (!dirr)
			chdir_ret = /* TODO: what should this be? */
				chdir((dirr = _getenv(info, "PWD=")) ? dirr : "/");
		else
			chdir_ret = chdir(dirr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ss);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dirr = _getenv(info, "OLDPWD=")) ? dirr : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - chnge da curr direc da proc
 * @info: Struc cont pot arg. To maint
 * const funct prot.
 * Return: Always nothing
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}

