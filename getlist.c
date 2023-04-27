#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @stri: str field of node
 * @num: node index used by nhistory
 *
 * Return: size of list
 */
lists_t *add_node(lists_t **head, const char *stri, int num)
{
	lists_t *new_nhead;

	if (!head)
		return (NULL);
	new_nhead = malloc(sizeof(lists_t));
	if (!new_nhead)
		return (NULL);
	_memset((void *)new_nhead, 0, sizeof(lists_t));
	new_nhead->num = num;
	if (stri)
	{
		new_nhead->stri = _strdup(stri);
		if (!new_nhead->stri)
		{
			free(new_nhead);
			return (NULL);
		}
	}
	new_nhead->next = *head;
	*head = new_nhead;
	return (new_nhead);
}

/**
 * added_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @stri: str field of node
 * @num: node index used by nhistory
 *
 * Return: size of list
 */
lists_t *added_node_end(lists_t **head, const char *stri, int num)
{
	lists_t *new_anode, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_anode = malloc(sizeof(lists_t));
	if (!new_anode)
		return (NULL);
	_memset((void *)new_anode, 0, sizeof(lists_t));
	new_anode->num = num;
	if (stri)
	{
		new_anode->stri = _strdup(stri);
		if (!new_anode->stri)
		{
			free(new_anode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_anode;
	}
	else
		*head = new_anode;
	return (new_anode);
}

/**
 * print_lists_str - prints only the str element of a lists_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lists_str(const lists_t *h)
{
	size_t c = 0;

	while (h)
	{
		_putsin(h->stri ? h->stri : "(nil)");
		_putsin("\n");
		h = h->next;
		c++;
	}
	return (c);
}

/**
 * delete_node_index - deletes node at given index
 * @head: address of pointer to first node
 * @nindex: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_index(lists_t **head, unsigned int nindex)
{
	lists_t *node, *prev_anode;
	unsigned int c = 0;

	if (!head || !*head)
		return (0);

	if (!nindex)
	{
		node = *head;
		*head = (*head)->next;
		free(node->stri);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (c == nindex)
		{
			prev_anode->next = node->next;
			free(node->stri);
			free(node);
			return (1);
		}
		c++;
		prev_anode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptri: address of pointer to head node
 *
 * Return: void
 */
void free_list(lists_t **head_ptri)
{
	lists_t *node, *next_anode, *head;

	if (!head_ptri || !*head_ptri)
		return;
	head = *head_ptri;
	node = head;
	while (node)
	{
		next_anode = node->next;
		free(node->stri);
		free(node);
		node = next_anode;
	}
	*head_ptri = NULL;
}
