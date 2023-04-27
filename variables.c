#include "shell.h"

/**
 * isit_chain - test if current char in buffer is a chain delimeter
 * @mes: the parameter struct
 * @mas: the char buffer
 * @d: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int isit_chain(mes_t *mes, char *mas, size_t *d)
{
	size_t g = *d;

	if (mas[g] == '|' && mas[g + 1] == '|')
	{
		mas[g] = 0;
		g++;
		mes->cmd_mas_type = CMD_OR;
	}
	else if (mas[g] == '&' && mas[g + 1] == '&')
	{
		mas[g] = 0;
		g++;
		mes->cmd_mas_type = CMD_AND;
	}
	else if (mas[g] == ';')
	{
		mas[g] = 0;
		mes->cmd_mas_type = CMD_CHAIN;
	}
	else
		return (0);
	*d = g;
	return (1);
}

/**
 * status_chain - checks we should continue chaining based on last status
 * @mes: the parameter struct
 * @mas: the char buffer
 * @d: address of current position in buf
 * @c: starting position in buf
 * @leng: length of buf
 *
 * Return: Void
 */
void status_chain(mes_t *mes, char *mas, size_t *d, size_t c, size_t leng)
{
	size_t g = *d;

	if (mes->cmd_mas_type == CMD_AND)
	{
		if (mes->status)
		{
			mas[c] = 0;
			g = leng;
		}
	}
	if (mes->cmd_mas_type == CMD_OR)
	{
		if (!mes->status)
		{
			mas[c] = 0;
			g = leng;
		}
	}

	*d = g;
}

/**
 * replace_aliass - replaces an aliases in the tokenized string
 * @mes: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliass(mes_t *mes)
{
	int c;
	lists_t *node;
	char *d;

	for (c = 0; c < 10; c++)
	{
		node = node_starts_prefix(mes->alias, mes->argv[0], '=');
		if (!node)
			return (0);
		free(mes->argv[0]);
		d = _locachr(node->stri, '=');
		if (!d)
			return (0);
		d = _strdup(d + 1);
		if (!d)
			return (0);
		mes->argv[0] = d;
	}
	return (1);
}

/**
 * replace_varss - replaces vars in the tokenized string
 * @mes: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varss(mes_t *mes)
{
	int c = 0;
	lists_t *node;

	for (c = 0; mes->argv[c]; c++)
	{
		if (mes->argv[c][0] != '$' || !mes->argv[c][1])
			continue;

		if (!_strcmp(mes->argv[c], "$?"))
		{
			replace_string(&(mes->argv[c]),
					_strdup(number_atoi(mes->status, 10, 0)));
			continue;
		}
		if (!_strcmp(mes->argv[c], "$$"))
		{
			replace_string(&(mes->argv[c]),
					_strdup(number_atoi(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_prefix(mes->env, &mes->argv[c][1], '=');
		if (node)
		{
			replace_string(&(mes->argv[c]),
					_strdup(_locachr(node->stri, '=') + 1));
			continue;
		}
		replace_string(&mes->argv[c], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @olds: address of old string
 * @news: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **olds, char *news)
{
	free(*olds);
	*olds = news;
	return (1);
}
