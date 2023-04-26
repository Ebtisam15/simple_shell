#include "shell.h"

/**
 * historylist - displays the history list, one command by line, starting at 0.
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int historylist(mes_t *mes)
{
	write_list(mes->nhistory);
	return (0);
}

/**
 * unalias_string - sets alias to string
 * @mes: parameter struct
 * @stri: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unalias_string(mes_t *mes, char *stri)
{
	char *cha, xter;
	int ber;

	cha = locate_xter(stri, '=');
	if (!cha)
		return (1);
	xter = *cha;
	*cha = 0;
	ber = node_deletion(&(mes->nalias),
		locate_index_node(mes->nalias, return_node_with(mes->nalias, stri, -1)));
	*cha = xter;
	return (ber);
}

/**
 * alias_string - sets alias to string
 * @mes: parameter struct
 * @stri: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_string(mes_t *mes, char *stri)
{
	char *cha;

	cha = locate_xter(stri, '=');
	if (!cha)
		return (1);
	if (!*++cha)
		return (unalias_string(mes, stri));

	unalias_string(mes, stri);
	return (node_at_end(&(mes->nalias), stri, 0) == NULL);
}

/**
 * wtire_alias - prints an alias string
 * @anode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int wtire_alias(lists_t *anode)
{
	char *cha = NULL, *b = NULL;

	if (anode)
	{
		cha = locate_xter(anode->stri, '=');
		for (b = anode->stri; b <= cha; b++)
		_putchar(*b);
		_putchar('\'');
		_instr(cha + 1);
		_instr("'\n");
		return (0);
	}
	return (1);
}

/**
 * copy_alias - copy the alias built-in
 * @mes: Structure containing potential arguments.
 *  Return: Always 0
 */
int copy_alias(mes_t *mes)
{
	int l = 0;
	char *cha = NULL;
	lists_t *anode = NULL;

	if (mes->argc == 1)
	{
		anode = mes->nalias;
		while (anode)
		{
			wtire_alias(anode);
			anode = anode->next;
		}
		return (0);
	}
	for (l = 1; mes->argv[l]; l++)
	{
		cha = locate_xter(mes->argv[l], '=');
		if (cha)
			alias_string(mes, mes->argv[l]);
		else
			wtire_alias(return_node_with(mes->nalias, mes->argv[l], '='));
	}

	return (0);
}
