#include "shell.h"

/**
 * lists_len - determines length of linked list
 * @nh: pointer to first node
 *
 * Return: size of list
 */
size_t lists_len(const lists_t *nh)
{
	size_t l = 0;

	while (nh)
	{
		nh = nh->next;
		l++;
	}
	return (l);
}

/**
 * lists_to_strings - returns an array of strings of the list->str
 * @nhead: pointer to first node
 *
 * Return: array of strings
 */
char **lists_to_strings(lists_t *nhead)
{
	lists_t *anode = nhead;
	size_t l = lists_len(nhead), k;
	char **stris;
	char *stri;

	if (!nhead || !l)
		return (NULL);
	stris = malloc(sizeof(char *) * (l + 1));
	if (!stris)
		return (NULL);
	for (l = 0; anode; anode = anode->next, l++)
	{
		stri = malloc(_strlen(anode->stri) + 1);
		if (!stri)
		{
			for (k = 0; k < l; k++)
				free(stris[l]);
			free(stris);
			return (NULL);
		}

		stri = _strcpy(stri, anode->stri);
		stris[l] = stri;
	}
	stris[l] = NULL;
	return (stris);
}

/**
 * write_list - prints all elements of a lists_t linked list
 * @nh: pointer to first node
 *
 * Return: size of list
 */
size_t write_list(const lists_t *nh)
{
	size_t l = 0;

	while (nh)
	{
		_instr(confun(nh->a, 10, 0));
		_putchar(':');
		_putchar(' ');
		_instr(nh->stri ? nh->stri : "(nil)");
		_instr("\n");
		nh = nh->next;
		l++;
	}
	return (l);
}

/**
 * return_node_with - returns node whose string starts with prefix
 * @anode: pointer to list head
 * @sprefix: string to match
 * @nc: the next character after prefix to match
 *
 * Return: match node or null
 */
lists_t *return_node_with(lists_t *anode, char *sprefix, char nc)
{
	char *pm = NULL;

	while (anode)
	{
		pm = needle_start_with(anode->stri, sprefix);
		if (pm && ((nc == -1) || (*pm == nc)))
			return (anode);
		anode = anode->next;
	}
	return (NULL);
}

/**
 * locate_index_node - gets the index of a node
 * @nhead: pointer to list head
 * @anode: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t locate_index_node(lists_t *nhead, lists_t *anode)
{
	size_t l = 0;

	while (nhead)
	{
		if (nhead == anode)
			return (l);
		nhead = nhead->next;
		l++;
	}
	return (-1);
}
