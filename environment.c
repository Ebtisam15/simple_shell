#include "shell.h"

/**
 * _myenvi - prints the current environmment
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenvi(mes_t *mes)
{
	print_lists_str(mes->env);
	return (0);
}

/**
 * _getenvi - gets the value of an environm variable
 * @mes: Structure containing potential arguments. Used to maintain
 * @named: env var name
 *
 * Return: the value
 */
char *_getenvi(mes_t *mes, const char *named)
{
	lists_t *node = mes->env;
	char *d;

	while (node)
	{
		d = start_with(node->stri, named);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenvi - Initialize a new environmment variable,
 *             or modify an existing one
 * @mes: Structure containing potential arguments.
 *  Return: Always 0
 */
int _mysetenvi(mes_t *mes)
{
	if (mes->argc != 3)
	{
		_printsti("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvi(mes, mes->argv[1], mes->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvi - Remove an environmment variable
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenvi(mes_t *mes)
{
	int c;

	if (mes->argc == 1)
	{
		_printsti("Too few arguements.\n");
		return (1);
	}
	for (c = 1; c <= mes->argc; c++)
		_unsetenvi(mes, mes->argv[c]);

	return (0);
}

/**
 * populate_envi_lists - populates env linked list
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_envi_lists(mes_t *mes)
{
	lists_t *node = NULL;
	size_t c;

	for (c = 0; environ[c]; c++)
		added_node_end(&node, environ[c], 0);
	mes->env = node;
	return (0);
}
