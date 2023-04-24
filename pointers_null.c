#include "shell.h"

/**
 * bfrees - frees a pointer and NULLs the address
 * @ptri: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfrees(void **ptri)
{
	if (ptri && *ptri)
	{
		free(*ptri);
		*ptri = NULL;
		return (1);
	}
	return (0);
}
