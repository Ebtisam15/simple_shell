#include "shell.h"

/**
 * _strncpy - copies a string.
 * @dest: the initial string
 * @src: the additional string
 * @n: number of bytes
 * Return: the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *a = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (x < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (a);
}

/**
 * _strncat - concatenates two strings
 * @b: the initial string
 * @c: the additional string
 * @l: number of charaters in a string
 *
 * Return: the resulting string.
 */

char *_strncat(char *b, char *c, int l)
{
	int x = 0;
	int y = 0;
	char *a = b;

	while (b[x] != '\0')
		x++;
	while (c[y] != '\0' && y < l)
	{
		b[x] = c[y];
		x++;
		y++;
	}
	if (y < l)
		b[x] = '\0';
	return (a);
}

/**
 * locate_xter - locates a character in a string
 * @a: the string to be parsed
 * @k: the character to look for
 * Return: a pointer to the memory area.
 */

char *locate_xter(char *a, char k)
{
	do {
		if (*a == k)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
