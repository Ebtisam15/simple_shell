#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const lists_t *h)
{
	size_t c = 0;

	while (h)
	{
		h = h->next;
		c++;
	}
	return (c);
}

/**
 * lists_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of string
 */
char **lists_to_strings(lists_t *head)
{
	lists_t *node = head;
	size_t c = list_len(head), g;
	char **strsi;
	char *stri;

	if (!head || !c)
		return (NULL);
	strsi = malloc(sizeof(char *) * (c + 1));
	if (!strsi)
		return (NULL);
	for (c = 0; node; node = node->next, c++)
	{
		stri = malloc(_strlen(node->stri) + 1);
		if (!stri)
		{
			for (g = 0; g < c; g++)
				free(strsi[g]);
			free(strsi);
			return (NULL);
		}

		stri = _strcpy(stri, node->stri);
		strsi[c] = stri;
	}
	strsi[c] = NULL;
	return (strsi);
}


/**
 * print_lists - prints all elements of a lists_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lists(const lists_t *h)
{
	size_t c = 0;

	while (h)
	{
		_putsin(number_atoi(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_putsin(h->stri ? h->stri : "(nil)");
		_putsin("\n");
		h = h->next;
		c++;
	}
	return (c);
}

/**
 * node_starts_prefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @a: the next character after prefix to match
 *
 * Return: match node or null
 */
lists_t *node_starts_prefix(lists_t *node, char *prefix, char a)
{
	char *d = NULL;

	while (node)
	{
		d = start_with(node->stri, prefix);
		if (d && ((a == -1) || (*d == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index_node - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_index_node(lists_t *head, lists_t *node)
{
	size_t c = 0;

	while (head)
	{
		if (head == node)
			return (c);
		head = head->next;
		c++;
	}
	return (-1);
}
