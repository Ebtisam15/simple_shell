#include "shell.h"

/**
 * _nnhistory - displays the nhistory list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @mes: Structure containing potential arguments.
 *  Return: Always 0
 */
int _nnhistory(mes_t *mes)
{
	print_lists(mes->nhistory);
	return (0);
}

/**
 * _unset_aliass - sets alias to string
 * @mes: parameter struct
 * @stri: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_aliass(mes_t *mes, char *stri)
{
	char *d, a;
	int reten;

	d = _locachr(stri, '=');
	if (!d)
		return (1);
	a = *d;
	*d = 0;
	reten = delete_node_index(&(mes->alias),
		get_index_node(mes->alias, node_starts_prefix(mes->alias, stri, -1)));
	*d = a;
	return (reten);
}

/**
 * set_aliass - sets alias to string
 * @mes: parameter struct
 * @stri: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_aliass(mes_t *mes, char *stri)
{
	char *d;

	d = _locachr(stri, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (_unset_aliass(mes, stri));

	_unset_aliass(mes, stri);
	return (added_node_end(&(mes->alias), stri, 0) == NULL);
}

/**
 * print_aliass - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_aliass(lists_t *node)
{
	char *d = NULL, *e = NULL;

	if (node)
	{
		d = _locachr(node->stri, '=');
		for (e = node->stri; e <= d; e++)
		_putchar(*e);
		_putchar('\'');
		_putsin(d + 1);
		_putsin("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myaliass - mimics the alias builtin (man alias)
 * @mes: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myaliass(mes_t *mes)
{
	int c = 0;
	char *d = NULL;
	lists_t *node = NULL;

	if (mes->argc == 1)
	{
		node = mes->alias;
		while (node)
		{
			print_aliass(node);
			node = node->next;
		}
		return (0);
	}
	for (c = 1; mes->argv[c]; c++)
	{
		d = _locachr(mes->argv[c], '=');
		if (d)
			set_aliass(mes, mes->argv[c]);
		else
			print_aliass(node_starts_prefix(mes->alias, mes->argv[c], '='));
	}

	return (0);
}

