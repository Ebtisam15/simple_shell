#include "shell.h"

/**
 * chain_delim - test if current char in buffer is a chain delimeter
 * @mes: the parameter struct
 * @m: the char buffer
 * @pm: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_delim(mes_t *mes, char *m, size_t *pm)
{
	size_t w = *pm;

	if (m[w] == '|' && m[w + 1] == '|')
	{
		m[w] = 0;
		w++;
		mes->cmd_m_type = CMD_OR;
	}
	else if (m[w] == '&' && m[w + 1] == '&')
	{
		m[w] = 0;
		w++;
		mes->cmd_m_type = CMD_AND;
	}
	else if (m[w] == ';')
	{
		m[w] = 0;
		mes->cmd_m_type = CMD_CHAIN;
	}
	else
		return (0);
	*pm = w;
	return (1);
}

/**
 * chain_status - checks we should continue chaining based on last status
 * @mes: the parameter struct
 * @m: the char buffer
 * @pm: address of current position in buf
 * @l: starting position in buf
 * @lm: length of buf
 *
 * Return: Void
 */
void chain_status(mes_t *mes, char *m, size_t *pm, size_t l, size_t lm)
{
	size_t w = *pm;

	if (mes->cmd_m_type == CMD_AND)
	{
		if (mes->status)
		{
			m[l] = 0;
			w = lm;
		}
	}
	if (mes->cmd_m_type == CMD_OR)
	{
		if (!mes->status)
		{
			m[l] = 0;
			w = lm;
		}
	}

	*pm = w;
}

/**
 * replace_aliases - replaces an aliases in the tokenized string
 * @mes: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliases(mes_t *mes)
{
	int l;
	lists_t *anode;
	char *pm;

	for (l = 0; l < 10; l++)
	{
		anode = return_node_with(mes->nalias, mes->argv[0], '=');
		if (!anode)
			return (0);
		free(mes->argv[0]);
		pm = locate_xter(anode->stri, '=');
		if (!pm)
			return (0);
		pm = dup_string(pm + 1);
		if (!pm)
			return (0);
		mes->argv[0] = pm;
	}
	return (1);
}

/**
 * replace_var - replaces vars in the tokenized string
 * @mes: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_var(mes_t *mes)
{
	int l = 0;
	lists_t *anode;

	for (l = 0; mes->argv[l]; l++)
	{
		if (mes->argv[l][0] != '$' || !mes->argv[l][1])
			continue;

		if (!_strcmp(mes->argv[l], "$?"))
		{
			re_string(&(mes->argv[l]),
					dup_string(confun(mes->status, 10, 0)));
			continue;
		}
		if (!_strcmp(mes->argv[l], "$$"))
		{
			re_string(&(mes->argv[l]),
					dup_string(confun(getpid(), 10, 0)));
			continue;
		}
		anode = return_node_with(mes->envi, &mes->argv[l][1], '=');
		if (anode)
		{
			re_string(&(mes->argv[l]),
					dup_string(locate_xter(anode->stri, '=') + 1));
			continue;
		}
		re_string(&mes->argv[l], dup_string(""));

	}
	return (0);
}

/**
 * re_string - replaces string
 * @olds: address of old string
 * @news: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int re_string(char **olds, char *news)
{
	free(*olds);
	*olds = news;
	return (1);
}
