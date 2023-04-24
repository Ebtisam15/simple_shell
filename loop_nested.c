#include "shell.h"

/**
 * hsh - main shell loop
 * @mes: the parameter & return mes struct
 * @ave: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(mes_t *mes, char **ave)
{
	ssize_t nr = 0;
	int builtin_nret = 0;

	while (nr != -1 && builtin_nret != -2)
	{
		clear_mes(mes);
		if (active(mes))
			_instr("$ ");
		_sprint(BUF_FLUSH);
		nr = line_without_new(mes);
		if (nr != -1)
		{
			set_mes(mes, ave);
			builtin_nret = find_builtinc(mes);
			if (builtin_nret == -1)
				find_cmdp(mes);
		}
		else if (active(mes))
			_putchar('\n');
		free_mes(mes, 0);
	}
	append_file(mes);
	free_mes(mes, 1);
	if (!active(mes) && mes->status)
		exit(mes->status);
	if (builtin_nret == -2)
	{
		if (mes->err_s == -1)
			exit(mes->status);
		exit(mes->err_s);
	}
	return (builtin_nret);
}

/**
 * find_builtinc - finds a builtin command
 * @mes: the parameter & return mes struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtinc(mes_t *mes)
{
	int l, built_in_nret = -1;
	builtin_tables builtintble[] = {
		{"exit", terminate},
		{"curenv", _curenv},
		{"help", _ccdpro},
		{"history", read_nhistory},
		{"new_env", new_env},
		{"re_env", re_env},
		{"change direct", _ccd},
		{"copy alias", copy_alias},
		{NULL, NULL}
	};

	for (l = 0; builtintble[l].typef; l++)
		if (_strcmp(mes->argv[0], builtintble[l].typef) == 0)
		{
			mes->count++;
			built_in_nret = builtintble[l].func(mes);
			break;
		}
	return (built_in_nret);
}

/**
 * find_cmdp - finds a command in path
 * @mes: the parameter & return mes struct
 *
 * Return: void
 */
void find_cmdp(mes_t *mes)
{
	char *npath = NULL;
	int l, kn;

	mes->npath = mes->argv[0];
	if (mes->count_this_line == 1)
	{
		mes->count++;
		mes->count_this_line = 0;
	}
	for (l = 0, kn = 0; mes->argv[l]; l++)
		if (!unique_ch(mes->argi[l], " \t\n"))
			kn++;
	if (!kn)
		return;

	npath = find_npath(mes, envar(mes, "NPATH="), mes->argv[0]);
	if (npath)
	{
		mes->npath = npath;
		run_cmd(mes);
	}
	else
	{
		if ((active(mes) || envar(mes, "NPATH=")
					|| mes->argv[0][0] == '/') && exe_cmd(mes, mes->argv[0]))
			run_cmd(mes);
		else if (*(mes->argi) != '\n')
		{
			mes->status = 127;
			ermes(mes, "not found\n");
		}
	}
}

/**
 * run_cmd - execute thread to run command
 * @mes: the parameter & return mes struct
 *
 * Return: void
 */
void run_cmd(mes_t *mes)
{
	pid_t pid_proid;

	pid_proid = fork();
	if (pid_proid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid_proid == 0)
	{
		if (execve(mes->npath, mes->argv, str_copy_env(mes)) == -1)
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
				ermes(mes, "Permission denied\n");
		}
	}
}
