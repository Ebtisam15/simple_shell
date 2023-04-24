#include "shell.h"

/**
 * mem_cbytes - fills memory with a constant byte
 * @a: the pointer to the memory area
 * @nb: the byte to fill *s with
 * @ab: the amount of bytes to be filled
 * Return: (a) a pointer to the memory area a
 */
char *mem_cbytes(char *a, char nb, unsigned int ab)
{
	unsigned int l;

	for (l = 0; l < ab; l++)
		a[l] = nb;
	return (a);
}

/**
 * ffrees - frees a string of strings
 * @sos: string of strings
 */
void ffrees(char **sos)
{
	char **nc = sos;

	if (!sos)
		return;
	while (*sos)
		free(*sos++);
	free(nc);
}

/**
 * _reallocblock - reallocates a block of memory
 * @ptri: pointer to previous malloc'ated block
 * @old_bsize: byte size of previous block
 * @new_bsize: byte size of new block
 *
 * Return: pointer to the old block name.
 */
void *_reallocblock(void *ptri, unsigned int old_bsize, unsigned int new_bsize)
{
	char *pm;

	if (!ptri)
		return (malloc(new_bsize));
	if (!new_bsize)
		return (free(ptri), NULL);
	if (new_bsize == old_bsize)
		return (ptri);

	pm = malloc(new_bsize);
	if (!pm)
		return (NULL);

	old_bsize = old_bsize < new_bsize ? old_bsize : new_bsize;
	while (old_bsize--)
		pm[old_bsize] = ((char *)ptri)[old_bsize];
	free(ptri);
	return (pm);
}
