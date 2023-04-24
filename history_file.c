#include "shell.h"

/**
 * ghistory_file  - gets the history file
 * @mes: parameter struct
 *
 * Return: allocated string contain history file
 */

char *ghistory_file(mes_t *mes)
{
	char *m, *dire;

	dire = envar(mes, "HOME=");
	if (!dire)
		return (NULL);
	m = malloc(sizeof(char) * (_strlen(dire) + _strlen(HISTOR_FILE) + 2));
	if (!m)
		return (NULL);
	m[0] = 0;
	_strcpy(m, dire);
	_strcat(m, "/");
	_strcat(m, HISTOR_FILE);
	return (m);
}

/**
 * append_file - creates a file, or appends to an existing file
 * @mes: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int append_file(mes_t *mes)
{
	ssize_t fd;
	char *filename = ghistory_file(mes);
	lists_t *anode = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (anode = mes->nhistory; anode; anode = anode->next)
	{
		_printsfd(anode->stri, fd);
		_sprintfd('\n', fd);
	}
	_sprintfd(M_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_nhistory - reads history from file
 * @mes: the parameter struct
 *
 * Return: historyscount on success, 0 otherwise
 */
int read_nhistory(mes_t *mes)
{
	int l, lasts = 0, linecounts = 0;
	ssize_t fd, rdlens, fsizes = 0;
	struct stat sti;
	char *m = NULL, *filename = ghistory_file(mes);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &sti))
		fsizes = sti.st_size;
	if (fsizes < 2)
		return (0);
	m = malloc(sizeof(char) * (fsizes + 1));
	if (!m)
		return (0);
	rdlens = read(fd, m, fsizes);
	m[fsizes] = 0;
	if (rdlens <= 0)
		return (free(m), 0);
	close(fd);
	for (l = 0; l < fsizes; l++)
		if (m[l] == '\n')
		{
			m[l] = 0;
			add_entry_history(mes, m + lasts, linecounts++);
			lasts = l + 1;
		}
	if (lasts != l)
		add_entry_history(mes, m + lasts, linecounts++);
	free(m);
	mes->historyscount = linecounts;
	while (mes->historyscount-- >= HISTOR_MAX)
		node_deletion(&(mes->nhistory), 0);
	resber_history(mes);
	return (mes->historyscount);
}

/**
 * add_entry_history - adds entry to a history linked list
 * @mes: Structure containing potential arguments. Used to maintain
 * @m: buffer
 * @linecounts: the history linecount, historyscount
 *
 * Return: Always 0
 */
int add_entry_history(mes_t *mes, char *m, int linecounts)
{
	lists_t *anode = NULL;

	if (mes->nhistory)
		anode = mes->nhistory;
	node_at_end(&anode, m, linecounts);

	if (!mes->nhistory)
		mes->nhistory = anode;
	return (0);
}

/**
 * resber_history - resbers the history linked list after changes
 * @mes: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historyscount
 */
int resber_history(mes_t *mes)
{
	lists_t *anode = mes->nhistory;
	int l = 0;

	while (anode)
	{
		anode->a = l++;
		anode = anode->next;
	}
	return (mes->historyscount = l);
}
