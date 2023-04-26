#include "shell.h"

/**
 * _curenv - prints the current environment
 * @mes: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _curenv(mes_t *mes)
{
	print_str_ele(mes->envi);
	return (0);
}

/**
 * envar - gets the value of an environ variable
 * @mes: Structure containing potential arguments. Used to maintain
 * @ename: envi var name
 *
 * Return: the value
 */
char *envar(mes_t *mes, const char *ename)
{
	lists_t *anode = mes->envi;
	char *cha;

	while (anode)
	{
		cha = needle_start_with(anode->stri, ename);
		if (cha && *cha)
			return (cha);
		anode = anode->next;
	}
	return (NULL);
}

/**
 * new_env - Initialize a new environment variable,
 *             or modify an existing one
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int new_env(mes_t *mes)
{
	if (mes->argc != 3)
	{
		sprint("Incorrect sber of arguements\n");
		return (1);
	}
	if (newen(mes, mes->argv[1], mes->argv[2]))
		return (0);
	return (1);
}

/**
 * re_env - Remove an environment variable
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int re_env(mes_t *mes)
{
	int l;

	if (mes->argc == 1)
	{
		sprint("little arguments.\n");
		return (1);
	}
	for (l = 1; l <= mes->argc; l++)
		rem_env_var(mes, mes->argv[l]);

	return (0);
}

/**
 * calculate_env_list - calculate environment linked list
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
int calculate_env_list(mes_t *mes)
{
	lists_t *anode = NULL;
	size_t l;
	const char *en[4096];

	for (l = 0; en[l]; l++)
		node_at_end(&anode, en[l], 0);
	mes->envi = anode;
	return (0);
}
