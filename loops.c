#include "shell.h"

/**
 * hsh - main shell loop
 * @mes: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(mes_t *mes, char **av)
{
	ssize_t h = 0;
	int builtin_reten = 0;

	while (h != -1 && builtin_reten != -2)
	{
		clear_mes(mes);
		if (_active(mes))
			_putsin("$ ");
		_eputchark(BUF_FLUSH);
		h = get_minus(mes);
		if (h != -1)
		{
			set_mes(mes, av);
			builtin_reten = find_built_in(mes);
			if (builtin_reten == -1)
				find_cmd(mes);
		}
		else if (_active(mes))
			_putchar('\n');
		free_mes(mes, 0);
	}
	write_nhistory(mes);
	free_mes(mes, 1);
	if (!_active(mes) && mes->status)
		exit(mes->status);
	if (builtin_reten == -2)
	{
		if (mes->err_code == -1)
			exit(mes->status);
		exit(mes->err_code);
	}
	return (builtin_reten);
}

/**
 * find_built_in - finds a builtin command
 * @mes: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_built_in(mes_t *mes)
{
	int c, built_in_ret = -1;
	built_in_table builtintble[] = {
		{"exit", _shellexit},
		{"env", _myenvi},
		{"help", _myhelper},
		{"nhistory", _nnhistory},
		{"setenv", _mysetenvi},
		{"unsetenv", _myunsetenvi},
		{"cd", _mycdir},
		{"alias", _myaliass},
		{NULL, NULL}
	};

	for (c = 0; builtintble[c].type; c++)
		if (_strcmp(mes->argv[0], builtintble[c].type) == 0)
		{
			mes->lines_count++;
			built_in_ret = builtintble[c].func(mes);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @mes: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(mes_t *mes)
{
	char *path = NULL;
	int c, i;

	mes->path = mes->argv[0];
	if (mes->linecount_flags == 1)
	{
		mes->lines_count++;
		mes->linecount_flags = 0;
	}
	for (c = 0, i = 0; mes->arg[c]; c++)
		if (!is_delimeter(mes->arg[c], " \t\n"))
			i++;
	if (!i)
		return;

	path = find_path(mes, _getenvi(mes, "PATH="), mes->argv[0]);
	if (path)
	{
		mes->path = path;
		fork_cmd(mes);
	}
	else
	{
		if ((_active(mes) || _getenvi(mes, "PATH=")
					|| mes->argv[0][0] == '/') && isit_cmd(mes, mes->argv[0]))
			fork_cmd(mes);
		else if (*(mes->arg) != '\n')
		{
			mes->status = 127;
			errprint(mes, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @mes: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(mes_t *mes)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(mes->path, mes->argv, get_environm(mes)) == -1)
		{
			free_mes(mes, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(mes->status));
		if (WIFEXITED(mes->status))
		{
			mes->status = WEXITSTATUS(mes->status);
			if (mes->status == 126)
				errprint(mes, "Permission denied\n");
		}
	}
}
