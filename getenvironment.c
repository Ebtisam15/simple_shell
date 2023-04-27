#include "shell.h"

/**
 * get_environm - returns the string array copy of our environm
 * @mes: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environm(mes_t *mes)
{
	if (!mes->environm || mes->envi_changed)
	{
		mes->environm = lists_to_strings(mes->env);
		mes->envi_changed = 0;
	}

	return (mes->environm);
}

/**
 * _unsetenvi - Remove an environmment variable
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenvi(mes_t *mes, char *var)
{
	lists_t *node = mes->env;
	size_t c = 0;
	char *d;

	if (!node || !var)
		return (0);

	while (node)
	{
		d = start_with(node->stri, var);
		if (d && *d == '=')
		{
			mes->envi_changed = delete_node_index(&(mes->env), c);
			c = 0;
			node = mes->env;
			continue;
		}
		node = node->next;
		c++;
	}
	return (mes->envi_changed);
}

/**
 * _setenvi - Initialize a new environmment variable,
 *             or modify an existing one
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @valued: the string env var value
 *  Return: Always 0
 */
int _setenvi(mes_t *mes, char *var, char *valued)
{
	char *mas = NULL;
	lists_t *node;
	char *d;

	if (!var || !valued)
		return (0);

	mes = malloc(_strlen(var) + _strlen(valued) + 2);
	if (!mas)
		return (1);
	_strcpy(mas, var);
	_strcat(mas, "=");
	_strcat(mas, valued);
	node = mes->env;
	while (node)
	{
		d = start_with(node->stri, var);
		if (d && *d == '=')
		{
			free(node->stri);
			node->stri = mas;
			mes->envi_changed = 1;
			return (0);
		}
		node = node->next;
	}
	added_node_end(&(mes->env), mas, 0);
	free(mas);
	mes->envi_changed = 1;
	return (0);
}
