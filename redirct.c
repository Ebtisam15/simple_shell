#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @c: the pointer to the memory area
 * @b: the byte
 * @f: the amount of bytes to be filled
 * Return: a pointer to the memory area
 */
char *_memset(char *c, char b, unsigned int f)
{
	unsigned int i;

	for (i = 0; i < f; i++)
		c[i] = b;
	return (c);
}

/**
 * ffree - frees a string of strings
 * @dd: string of strings
 */
void ffree(char **dd)
{
	char **a = dd;

	if (!dd)
		return;
	while (*dd)
		free(*dd++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptri: pointer to previous malloc'ated block
 * @old_sizes: byte size of previous block
 * @new_sizes: byte size of new block
 *
 * Return: pointer to da ol'block nameden.
 */
void *_realloc(void *ptri, unsigned int old_sizes, unsigned int new_sizes)
{
	char *d;

	if (!ptri)
		return (malloc(new_sizes));
	if (!new_sizes)
		return (free(ptri), NULL);
	if (new_sizes == old_sizes)
		return (ptri);

	d = malloc(new_sizes);
	if (!d)
		return (NULL);

	old_sizes = old_sizes < new_sizes ? old_sizes : new_sizes;
	while (old_sizes--)
		d[old_sizes] = ((char *)ptri)[old_sizes];
	free(ptri);
	return (d);
}
