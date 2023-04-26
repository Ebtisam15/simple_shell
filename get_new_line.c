#include "shell.h"

/**
 * enter_buff - buffers chained commands
 * @mes: parameter struct
 * @m: address of buffer
 * @ladd: address of len var
 *
 * Return: bytes read
 */
ssize_t enter_buff(mes_t *mes, char **m, size_t *ladd)
{
	ssize_t c = 0;
	size_t lcha = 0;

	if (!*ladd)
	{
		free(*m);
		*m = NULL;
		signal(SIGINT, block_ctrl_c);
#if GETLINE
		c = get_next_line(m, &lcha, stdin);
#else
		c = get_next_line(mes, m, &lcha);
#endif
		if (c > 0)
		{
			if ((*m)[c - 1] == '\n')
			{
				(*m)[c - 1] = '\0';
				c--;
			}
			mes->count_this_line = 1;
			funrep(*m);
			add_entry_history(mes, *m, mes->historyscount++);
			{
				*ladd = c;
				mes->cmd_m = m;
			}
		}
	}
	return (c);
}

/**
 * line_without_new - gets a line minus the newline
 * @mes: parameter struct
 *
 * Return: bytes read
 */
ssize_t line_without_new(mes_t *mes)
{
	static char *m;
	static size_t l, k, ladd;
	ssize_t c = 0;
	char **m_p = &(mes->argi), *pm;

	_putchar(M_FLUSH);
	c = enter_buff(mes, &m, &ladd);
	if (c == -1)
		return (-1);
	if (ladd)
	{
		k = l;
		pm = m + l;

		chain_status(mes, m, &k, l, ladd);
		while (k < ladd)
		{
			if (chain_delim(mes, m, &k))
				break;
			k++;
		}

		l = k + 1;
		if (l >= ladd)
		{
			l = ladd = 0;
			mes->cmd_m_type = CMD_NORMAL;
		}

		*m_p = pm;
		return (_strlen(pm));
	}

	*m_p = m;
	return (c);
}

/**
 * read_m - reads a buffer
 * @mes: parameter struct
 * @m: buffer
 * @l: size
 *
 * Return: c
 */
ssize_t read_m(mes_t *mes, char *m, size_t *l)
{
	ssize_t c = 0;

	if (*l)
		return (0);
	c = read(mes->readfd, m, READ_M_SIZE);
	if (c >= 0)
		*l = c;
	return (c);
}

/**
 * get_next_line - gets the next line of input from STDIN
 * @mes: parameter struct
 * @ptri: address of pointer to buffer, preallocated or NULL
 * @ptr_m: size of preallocated ptr buffer if not NULL
 *
 * Return: a
 */
int get_next_line(mes_t *mes, char **ptri, size_t *ptr_m)
{
	static char m[READ_M_SIZE];
	static size_t l, ladd;
	size_t f;
	ssize_t c = 0, a = 0;
	char *pm = NULL, *new_pm = NULL, *d;

	pm = *ptri;
	if (pm && ptr_m)
		a = *ptr_m;
	if (l == ladd)
		l = ladd = 0;

	c = read_m(mes, m, &ladd);
	if (c == -1 || (c == 0 && ladd == 0))
		return (-1);

	d = locate_xter(m + l, '\n');
	f = d ? 1 + (unsigned int)(d - m) : ladd;
	new_pm = _reallocblock(pm, a, a ? a + f : f + 1);
	if (!new_pm)
		return (pm ? free(pm), -1 : -1);

	if (a)
		_strncat(new_pm, m + l, f - l);
	else
		_strncpy(new_pm, m + l, f - l + 1);

	a += f - l;
	l = f;
	pm = new_pm;

	if (ptr_m)
		*ptr_m = a;
	*ptri = pm;
	return (a);
}

/**
 * block_ctrl_c - blocks ctrl-C
 * @signal_s: the signal sber
 *
 * Return: void
 */
void block_ctrl_c(__attribute__((unused))int signal_s)
{
	_instr("\n");
	_instr("$ ");
	_putchar(M_FLUSH);
}
