#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @b: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *b)
{
	int c = 0;

	if (!b)
		return (0);

	while (*b++)
		c++;
	return (c);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @b1: the first strang
 * @b2: the second strang
 *
 * Return: negative if b1 < b2, positive if b1 > b2, zero if b1 == b2
 */
int _strcmp(char *b1, char *b2)
{
	while (*b1 && *b2)
	{
		if (*b1 != *b2)
			return (*b1 - *b2);
		b1++;
		b2++;
	}
	if (*b1 == *b2)
		return (0);
	else
		return (*b1 < *b2 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @haystacks: string to search
 * @needles: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *haystacks, const char *needles)
{
	while (*needles)
		if (*needles++ != *haystacks++)
			return (NULL);
	return ((char *)haystacks);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *reten = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (reten);
}
