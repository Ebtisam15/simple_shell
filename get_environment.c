#include "shell.h"

/**
 * str_copy_env - returns the string array copy of our environment
 * @mes: Structure containing potential arguments.
 * Return: Always 0
 */
char **str_copy_env(mes_t *mes)
{
	if (!mes->environm || mes->envi_changed)
	{
		mes->environm = lists_to_strings(mes->envi);
		mes->envi_changed = 0;
	}

	return (mes->environm);
}

/**
 * rem_env_var - Remove an environment variable
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @env_var: the string env var property
 */
int rem_env_var(mes_t *mes, char *env_var)
{
	lists_t *anode = mes->envi;
	size_t l = 0;
	char *pm;

	if (!anode || !env_var)
		return (0);

	while (anode)
	{
		pm = needle_start_with(anode->stri, env_var);
		if (pm && *pm == '=')
		{
			mes->envi_changed = node_deletion(&(mes->envi), l);
			l = 0;
			anode = mes->envi;
			continue;
		}
		anode = anode->next;
		l++;
	}
	return (mes->envi_changed);
}

/**
 * newen - Initialize a new environment variable,
 *             or modify an existing one
 * @mes: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @env_var: the string env var property
 * @env_value: the string env var value
 *  Return: Always 0
 */
int newen(mes_t *mes, char *env_var, char *env_value)
{
	char *m = NULL;
	lists_t *anode;
	char *pm;

	if (!env_var || !env_value)
		return (0);

	m = malloc(_strlen(env_var) + _strlen(env_value) + 2);
	if (!m)
		return (1);
	_strcpy(m, env_var);
	_strcat(m, "=");
	_strcat(m, env_value);
	anode = mes->envi;
	while (anode)
	{
		pm = needle_start_with(anode->stri, env_var);
		if (pm && *pm == '=')
		{
			free(anode->stri);
			anode->stri = m;
			mes->envi_changed = 1;
			return (0);
		}
		anode = anode->next;
	}
	node_at_end(&(mes->envi), m, 0);
	free(m);
	mes->envi_changed = 1;
	return (0);
}
