#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant_function prototype.
 * Return: exits with a given exit status
 * (0) info.argov[0] != "exit"
 */
int _myexit(informt *info)
{
	int exit_checks;

	if (info->argov[1]) /* If there_is exit arguement */
	{
		exit_checks = _erratoi(info->argov[1]);
		if (exit_checks == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argov[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argov[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(informt *info)
{
	char *s, *dir, buffer[1024];
	int chdirectory-ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argov[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdirectory-ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdirectory-ret = chdir(dir);
	}
	else if (_strcmp(info->argov[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirectory-ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirectory-ret = chdir(info->argov[1]);
	if (chdirectory-ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argov[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constantfunction prototype.
 * Return: Always 0 . 
 */
int _myhelp(informt *info)
{
	char **arg_array;

	arg_array = info->argov;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
