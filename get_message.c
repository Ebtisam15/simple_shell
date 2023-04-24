#include "shell.h"

/**
 * clear_mes - initializes mes_t struct
 * @mes: struct address
 */
void clear_mes(mes_t *mes)
{
	mes->argi = NULL;
	mes->argv = NULL;
	mes->npath = NULL;
	mes->argc = 0;
}

/**
 * set_mes - initializes mes_t struct
 * @mes: struct address
 * @ave: argument vector
 */
void set_mes(mes_t *mes, char **ave)
{
	int l = 0;

	mes->filen = ave[0];
	if (mes->argi)
	{
		mes->argv = string_into(mes->argi, " \t");
		if (!mes->argv)
		{
			mes->argv = malloc(sizeof(char *) * 2);
			if (mes->argv)
			{
				mes->argv[0] = dup_string(mes->argi);
				mes->argv[1] = NULL;
			}
		}
		for (l = 0; mes->argv && mes->argv[l]; l++)
			;
		mes->argc = l;

		replace_aliases(mes);
		replace_var(mes);
	}
}

/**
 * free_mes - frees mes_t struct fields
 * @mes: struct address
 * @fall: true if freeing all fields
 */
void free_mes(mes_t *mes, int fall)
{
	ffrees(mes->argv);
	mes->argv = NULL;
	mes->npath = NULL;
	if (fall)
	{
		if (!mes->cmd_m)
			free(mes->argi);
		if (mes->envi)
			free_lists(&(mes->envi));
		if (mes->nhistory)
			free_lists(&(mes->nhistory));
		if (mes->nalias)
			free_lists(&(mes->nalias));
		ffrees(mes->environm);
			mes->environm = NULL;
		bfrees((void **)mes->cmd_m);
		if (mes->readfd > 2)
			close(mes->readfd);
		_putchar(BUF_FLUSH);
	}
}
