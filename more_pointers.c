#include "shell.h"

/**
 * _strcmp - compare string values
 * @a1: input value
 * @a2: input value
 * Return: comparison
 */

int _strcmp(char *a1, char *a2)
{

	while (*a1 && *a2)
	{
		if (*a1 != *a2)
		{
			return (*a1 - *a2);
		}
		a1++;
		a2++;
	}
	if (*a1 == *a2)
		return (0);
	else
		return (*a1 < *a2 ? -1 : 1);
}

/**
 * _strcat - concatenates two strings.
 * @dest: a destination string.
 * @src: additional string
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
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
	int l = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[l])
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = 0;
	return (dest);
}
