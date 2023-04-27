#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@f: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int f)
{
	int c, g;
	char *b = dest;

	c = 0;
	while (src[c] != '\0' && c < f - 1)
	{
		dest[c] = src[c];
		c++;
	}
	if (c < f)
	{
		g = c;
		while (g < f)
		{
			dest[g] = '\0';
			g++;
		}
	}
	return (b);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@f: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int f)
{
	int c, g;
	char *b = dest;

	c = 0;
	g = 0;
	while (dest[c] != '\0')
		c++;
	while (src[g] != '\0' && g < f)
	{
		dest[c] = src[g];
		c++;
		g++;
	}
	if (g < f)
		dest[g] = '\0';
	return (b);
}

/**
 **_locachr - locates a character in a string
 *@b: the string to be parsed
 *@a: the character to look for
 *Return: a pointer to the memory area
 */
char *_locachr(char *b, char a)
{
	do {
		if (*b == a)
			return (b);
	} while (*b++ != '\0');

	return (NULL);
}

