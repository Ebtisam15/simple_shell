#include "shell.h"

/**
 * clear_mes - initializes mes_t struct
 * @mes: struct address
 */
void clear_mes(mes_t *mes)
{
	mes->arg = NULL;
	mes->argv = NULL;
	mes->path = NULL;
	mes->argc = 0;
}

/**
 * set_mes - initializes mes_t struct
 * @mes: struct address
 * @av: argument vector
 */
void set_mes(mes_t *mes, char **av)
{
	int c = 0;

	mes->fnamed = av[0];
	if (mes->arg)
	{
		mes->argv = strtow(mes->arg, " \t");
		if (!mes->argv)
		{
			mes->argv = malloc(sizeof(char *) * 2);
			if (mes->argv)
			{
				mes->argv[0] = _strdup(mes->arg);
				mes->argv[1] = NULL;
			}
		}
		for (c = 0; mes->argv && mes->argv[c]; c++)
			;
		mes->argc = c;

		replace_aliass(mes);
		replace_varss(mes);
	}
}

/**
 * free_mes - frees mes_t struct fields
 * @mes: struct address
 * @tall: true if freeing all fields
 */
void free_mes(mes_t *mes, int tall)
{
	ffree(mes->argv);
	mes->argv = NULL;
	mes->path = NULL;
	if (tall)
	{
		if (!mes->cmd_mas)
			free(mes->arg);
		if (mes->env)
			free_list(&(mes->env));
		if (mes->nhistory)
			free_list(&(mes->nhistory));
		if (mes->alias)
			free_list(&(mes->alias));
		ffree(mes->environm);
			mes->environm = NULL;
		bfree((void **)mes->cmd_mas);
		if (mes->readfd > 2)
			close(mes->readfd);
		_putchar(BUF_FLUSH);
	}
}
