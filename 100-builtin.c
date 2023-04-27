#include "shell.h"

/**
 * _shellexit - exits the shell
 * @mes: Structure containing potential arguments.
 * Return: exits with a given exit status
 */
int _shellexit(mes_t *mes)
{
	int exitstatus;

	if (mes->argv[1])
	{
		exitstatus = _erroratoi(mes->argv[1]);
		if (exitstatus == -1)
		{
			mes->status = 2;
			errprint(mes, "Illegal number: ");
			_printsti(mes->argv[1]);
			_eputchark('\n');
			return (1);
		}
		mes->err_code = _erroratoi(mes->argv[1]);
		return (-2);
	}
	mes->err_code = -1;
	return (-2);
}

/**
 * _mycdir - changes the current directory of the process
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int _mycdir(mes_t *mes)
{
	char *b, *dire, m[1024];
	int chdir_reten;

	b = getcwd(m, 1024);
	if (!b)
		_putsin("TODO: >>getcwd failure emsg here<<\n");
	if (!mes->argv[1])
	{
		dire = _getenvi(mes, "HOME=");
		if (!dire)
			chdir_reten = chdir((dire = _getenvi(mes, "PWD=")) ? dire : "/");
		else
			chdir_reten = chdir(dire);
	}
	else if (_strcmp(mes->argv[1], "-") == 0)
	{
		if (!_getenvi(mes, "OLDPWD="))
		{
			_putsin(b);
			_putchar('\n');
			return (1);
		}
		_putsin(_getenvi(mes, "OLDPWD=")), _putchar('\n');
		chdir_reten = chdir((dire = _getenvi(mes, "OLDPWD=")) ? dire : "/");
	}
	else
		chdir_reten = chdir(mes->argv[1]);
	if (chdir_reten == -1)
	{
		errprint(mes, "can't cd to ");
		_printsti(mes->argv[1]), _eputchark('\n');
	}
	else
	{
		_setenvi(mes, "OLDPWD", _getenvi(mes, "PWD="));
		_setenvi(mes, "PWD", getcwd(m, 1024));
	}
	return (0);
}

/**
 * _myhelper - changes the current directory of the process
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelper(mes_t *mes)
{
	char **argv_array;

	argv_array = mes->argv;
	_putsin("help call works. Function not yet implemented \n");
	if (0)
		_putsin(*argv_array);
	return (0);
}
