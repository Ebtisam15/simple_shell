#include "shell.h"

/**
 * get_nhistory_file - gets the nhistory file
 * @mes: parameter struct
 *
 * Return: allocated string containg nhistory file
 */

char *get_nhistory_file(mes_t *mes)
{
	char *mas, *dire;

	dire = _getenvi(mes, "HOME=");
	if (!dire)
		return (NULL);
	mas = malloc(sizeof(char) * (_strlen(dire) + _strlen(HIST_FILE) + 2));
	if (!mas)
		return (NULL);
	mas[0] = 0;
	_strcpy(mas, dire);
	_strcat(mas, "/");
	_strcat(mas, HIST_FILE);
	return (mas);
}

/**
 * write_nhistory - creates a file, or appends to an existing file
 * @mes: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_nhistory(mes_t *mes)
{
	ssize_t fd;
	char *filenamed = get_nhistory_file(mes);
	lists_t *node = NULL;

	if (!filenamed)
		return (-1);

	fd = open(filenamed, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenamed);
	if (fd == -1)
		return (-1);
	for (node = mes->nhistory; node; node = node->next)
	{
		_putsinfd(node->stri, fd);
		_putinfd('\n', fd);
	}
	_putinfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_nhistory - reads nhistory from file
 * @mes: the parameter struct
 *
 * Return: histcounts on success, 0 otherwise
 */
int read_nhistory(mes_t *mes)
{
	int c, lasts = 0, linecounts = 0;
	ssize_t fd, rdlens, fsizes = 0;
	struct stat sti;
	char *mas = NULL, *filenamed = get_nhistory_file(mes);

	if (!filenamed)
		return (0);

	fd = open(filenamed, O_RDONLY);
	free(filenamed);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &sti))
		fsizes = sti.st_size;
	if (fsizes < 2)
		return (0);
	mas = malloc(sizeof(char) * (fsizes + 1));
	if (!mas)
		return (0);
	rdlens = read(fd, mas, fsizes);
	mas[fsizes] = 0;
	if (rdlens <= 0)
		return (free(mas), 0);
	close(fd);
	for (c = 0; c < fsizes; c++)
		if (mas[c] == '\n')
		{
			mas[c] = 0;
			build_nhistory_list(mes, mas + lasts, linecounts++);
			lasts = c + 1;
		}
	if (lasts != c)
		build_nhistory_list(mes, mas + lasts, linecounts++);
	free(mas);
	mes->histcounts = linecounts;
	while (mes->histcounts-- >= HIST_MAX)
		delete_node_index(&(mes->nhistory), 0);
	renumber_nhistory(mes);
	return (mes->histcounts);
}

/**
 * build_nhistory_list - adds entry to a nhistory linked list
 * @mes: Structure containing potential arguments. Used to maintain
 * @mas: buffer
 * @linecounts: the nhistory linecount, histcounts
 *
 * Return: Always 0
 */
int build_nhistory_list(mes_t *mes, char *mas, int linecounts)
{
	lists_t *node = NULL;

	if (mes->nhistory)
		node = mes->nhistory;
	added_node_end(&node, mas, linecounts);

	if (!mes->nhistory)
		mes->nhistory = node;
	return (0);
}

/**
 * renumber_nhistory - renumbers the nhistory linked list after changes
 * @mes: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcounts
 */
int renumber_nhistory(mes_t *mes)
{
	lists_t *node = mes->nhistory;
	int c = 0;

	while (node)
	{
		node->num = c++;
		node = node->next;
	}
	return (mes->histcounts = c);
}

