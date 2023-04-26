#include "shell.h"

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 * Return: s1[i] - s2[i]
 */

int _strcmp(char *s1, char *s2)
{
	int x = 0;

	while (s1[x] != '\0' && s2[x] != '\0')
	{
		if (s1[x] != s2[x])
		{
			return (s1[x] - s2[x]);
		}
		x++;
	}
	return (0);
}

/**
 * _strcat - concatenates two strings.
 * @dest: a destination string.
 * @src: additional string
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int dl = 0;
	int sl = 0;
	int x;

	for (x = 0 ; dest[x] != '\0' ; x++)
		dl++;
	for (x = 0 ; src[x] != '\0' ; x++)
		sl++;
	for (x = 0 ; x <= sl; x++)
		dest[dl + x] = src[x];
	return (dest);
}

/**
 * _strlen - returns the length of a string.
 * @a: a string
 * Return: length of a string
 */
int _strlen(char *a)
{
	int ladd = 0;

	if (!a)
		return (0);

	while (*a != '\0')
	{
		ladd++;
	}

	return (ladd);
}

/**
 * *_strcpy - copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: the string
 */

char *_strcpy(char *dest, char *src)
{
	int x = 0;
	int y = 0;

	while (*(src + x) != '\0')
	{
		x++;
	}
	for ( ; y < x; y++)
	{
		dest[y] = src[y];
	}
	dest[x] = '\0';
	return (dest);
}
