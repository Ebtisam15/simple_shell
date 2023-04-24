#include "shell.h"

/**
 * terminate - terminate the shell
 * @mes: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: terminate with a given termination status
 * (0) if stru.argv[0] != "terminate"
 */
int terminate(mes_t *mes)
{
	int termcheck;

	if (mes->argv[1])
	{
		termcheck = intatoi(mes->argv[1]);
		if (termcheck == -1)
		{
			mes->status = 2;
			ermes(mes, "Illegal number: ");
			sprint(mes->argv[1]);
			_sprint('\n');
			return (1);
		}
		mes->err_s = intatoi(mes->argv[1]);
		return (-2);
	}
	mes->err_s = -1;
	return (-2);
}

/**
 * _ccd - changes the current directory of the process
 * @mes: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _ccd(mes_t *mes)
{
	char *a, *z, m[1024];
	int y;

	a = getcwd(m, 1024);
	if (!a)
		_instr("RESPONSE: >>getcwd failured here<<\n");
	if (!mes->argv[1])
	{
		z = envar(mes, "HOME=");
		if (!z)
			y = chdir((z = envar(mes, "PWD=")) ? z : "/");
		else
			y = chdir(z);
	}
	else if (_strcmp(mes->argv[1], "-") == 0)
	{
		if (!envar(mes, "OLDPWD="))
		{
			_instr(a);
			_putchar('\n');
			return (1);
		}
		_instr(envar(mes, "OLDPWD=")), _putchar('\n');
		y = chdir((z = envar(mes, "OLDPWD=")) ? z : "/");
	}
	else
		y = chdir(mes->argv[1]);
	if (y == -1)
	{
		ermes(mes, "can't ccd to ");
		sprint(mes->argv[1]), _sprint('\n');
	}
	else
	{
		newen(mes, "OLDPWD", envar(mes, "PWD="));
		newen(mes, "PWD", getcwd(m, 1024));
	}
	return (0);
}

/**
 * _ccdpro - changes the current directory of the process
 * @mes: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _ccdpro(mes_t *mes)
{
	char **arr;

	arr = mes->argv;
	_instr("help call works. Function not yet implemented \n");
	if (0)
		_instr(*arr);
	return (0);
}
