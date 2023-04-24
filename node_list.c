#include "shell.h"

/**
 * add_anode - adds a node to the start of the list
 * @nhead: address of pointer to head node
 * @stri: str field of node
 * @a: node index used by history
 *
 * Return: size of list
 */
lists_t *add_anode(lists_t **nhead, const char *stri, int a)
{
	lists_t *new_nhead;

	if (!nhead)
		return (NULL);
	new_nhead = malloc(sizeof(lists_t));
	if (!new_nhead)
		return (NULL);
	mem_cbytes((void *)new_nhead, 0, sizeof(lists_t));
	new_nhead->a = a;
	if (stri)
	{
		new_nhead->stri = dup_string(stri);
		if (!new_nhead->stri)
		{
			free(new_nhead);
			return (NULL);
		}
	}
	new_nhead->next = *nhead;
	*nhead = new_nhead;
	return (new_nhead);
}

/**
 * node_at_end - adds a node to the end of the list
 * @nhead: address of pointer to head node
 * @stri: str field of node
 * @a: node index used by history
 *
 * Return: size of list
 */
lists_t *node_at_end(lists_t **nhead, const char *stri, int a)
{
	lists_t *new_anode, *anode;

	if (!nhead)
		return (NULL);

	anode = *nhead;
	new_anode = malloc(sizeof(lists_t));
	if (!new_anode)
		return (NULL);
	mem_cbytes((void *)new_anode, 0, sizeof(lists_t));
	new_anode->a = a;
	if (stri)
	{
		new_anode->stri = dup_string(stri);
		if (!new_anode->stri)
		{
			free(new_anode);
			return (NULL);
		}
	}
	if (anode)
	{
		while (anode->next)
			anode = anode->next;
		anode->next = new_anode;
	}
	else
		*nhead = new_anode;
	return (new_anode);
}

/**
 * print_str_ele - prints only the str element of a lists_t linked list
 * @nh: pointer to first node
 *
 * Return: size of list
 */
size_t print_str_ele(const lists_t *nh)
{
	size_t l = 0;

	while (nh)
	{
		_instr(nh->stri ? nh->stri : "(nil)");
		_instr("\n");
		nh = nh->next;
		l++;
	}
	return (l);
}

/**
 * node_deletion - deletes node at given index
 * @nhead: address of pointer to first node
 * @nindex: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int node_deletion(lists_t **nhead, unsigned int nindex)
{
	lists_t *anode, *prev_anode;
	unsigned int l = 0;

	if (!nhead || !*nhead)
		return (0);

	if (!nindex)
	{
		anode = *nhead;
		*nhead = (*nhead)->next;
		free(anode->stri);
		free(anode);
		return (1);
	}
	anode = *nhead;
	while (anode)
	{
		if (l == nindex)
		{
			prev_anode->next = anode->next;
			free(anode->stri);
			free(anode);
			return (1);
		}
		l++;
		prev_anode = anode;
		anode = anode->next;
	}
	return (0);
}

/**
 * free_lists - frees all nodes of a list
 * @nhead_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lists(lists_t **nhead_ptr)
{
	lists_t *anode, *next_anode, *nhead;

	if (!nhead_ptr || !*nhead_ptr)
		return;
	nhead = *nhead_ptr;
	anode = nhead;
	while (anode)
	{
		next_anode = anode->next;
		free(anode->stri);
		free(anode);
		anode = next_anode;
	}
	*nhead_ptr = NULL;
}
