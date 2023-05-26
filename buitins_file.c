#include "shell.h"

/**
 * _myexit - func that exits the shell
 * @info: Structure containing potential arguments used to maintain
 * 	constant function prototype.
 *  Return: given exit status on exit,
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If exit arguement exist */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
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
 * _mycd - func that changes the current directory of the process
 * @info: Structure containing potential arguments used to maintain
 *          constant function prototype
 *  Return: 0 Always
 */
int _mycd(info_t *info)
{
	char *x, *dir1, buffer[1024];
	int chddir_ret;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir1 = _getenv(info, "HOME=");
		if (!dir1)
			chddir_ret = /* TODO: what should go here? */
				chddir((dir1 = _getenv(info, "PWD=")) ? dir1 : "/");
		else
			chddir_ret = chddir(dir1);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		} 
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chddir_ret = /* TODO: what should go here? */
			chddir((dir1 = _getenv(info, "OLDPWD=")) ? dir1 : "/");
	}
	else
		chddir_ret = chddir(info->argv[1]);
	if (chddir_ret == -1)
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
 * _myhelp - func that changes the current directory of the process
 * @info: Structure containing potential arguments used to maintain
 * 	constant function prototype.
 *  Return: 0 Always
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
