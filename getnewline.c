#include "shell.h"

/**
 * input_mas - buffers chained commands
 * @mes: parameter struct
 * @mas: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t input_mas(mes_t *mes, char **mas, size_t *leng)
{
	ssize_t h = 0;
	size_t len_d = 0;

	if (!*leng)
	{
		/*bfree((void **)->cmd_mas);*/
		free(*mas);
		*mas = NULL;
		signal(SIGINT, siginHandler);
#if USE_GETLINE
		h = getline(mas, &len_d, stdin);
#else
		h = _getlinen(mes, mas, &len_d);
#endif
		if (h > 0)
		{
			if ((*mas)[h - 1] == '\n')
			{
				(*mas)[h - 1] = '\0';
				h--;
			}
			mes->linecount_flags = 1;
			func_replace(*mas);
			build_nhistory_list(mes, *mas, mes->histcounts++);
			if (_locachr(*mas, ';'))
			{
				*leng = h;
				mes->cmd_mas = mas;
			}
		}
	}
	return (h);
}

/**
 * get_minus - gets a line minus the newline
 * @mes: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_minus(mes_t *mes)
{
	static char *mas;
	static size_t c, g, leng;
	ssize_t h = 0;
	char **mas_d = &(mes->arg), *d;

	_putchar(BUF_FLUSH);
	h = input_mas(mes, &mas, &leng);
	if (h == -1)
		return (-1);
	if (leng)
	{
		g = c;
		d = mas + c;

		status_chain(mes, mas, &g, c, leng);
		while (g < leng)
		{
			if (isit_chain(mes, mas, &g))
				break;
			g++;
		}

		c = g + 1;
		if (c >= leng)
		{
			c = leng = 0;
			mes->cmd_mas_type = CMD_NORM;
		}

		*mas_d = d;
		return (_strlen(d));
	}

	*mas_d = mas;
	return (h);
}

/**
 * read_mas - reads a buffer
 * @mes: parameter struct
 * @mas: buffer
 * @c: size
 *
 * Return: h
 */
ssize_t read_mas(mes_t *mes, char *mas, size_t *c)
{
	ssize_t h = 0;

	if (*c)
		return (0);
	h = read(mes->readfd, mas, READ_MAS_SIZE);
	if (h >= 0)
		*c = h;
	return (h);
}

/**
 * _getlinen - gets the next line of input from STDIN
 * @mes: parameter struct
 * @ptri: address of pointer to buffer, preallocated or NULL
 * @lengt: size of preallocated ptr buffer if not NULL
 *
 * Return: b
 */
int _getlinen(mes_t *mes, char **ptri, size_t *lengt)
{
	static char mas[READ_MAS_SIZE];
	static size_t c, leng;
	size_t i;
	ssize_t h = 0, b = 0;
	char *d = NULL, *new_d = NULL, *a;

	d = *ptri;
	if (d && lengt)
		b = *lengt;
	if (c == leng)
		c = leng = 0;

	h = read_mas(mes, mas, &leng);
	if (h == -1 || (h == 0 && leng == 0))
		return (-1);

	a = _locachr(mas + c, '\n');
	i = a ? 1 + (unsigned int)(a - mas) : leng;
	new_d = _realloc(d, b, b ? b + i : i + 1);
	if (!new_d)
		return (d ? free(d), -1 : -1);

	if (b)
		_strncat(new_d, mas + c, i - c);
	else
		_strncpy(new_d, mas + c, i - c + 1);

	b += i - c;
	c = i;
	d = new_d;

	if (lengt)
		*lengt = b;
	*ptri = d;
	return (b);
}

/**
 * siginHandler - blocks ctrl-C
 * @sig_number: the signal number
 *
 * Return: void
 */
void siginHandler(__attribute__((unused))int sig_number)
{
	_putsin("\n");
	_putsin("$ ");
	_putchar(BUF_FLUSH);
}
