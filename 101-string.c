#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int c = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[c])
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @stri: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *stri)
{
	int lengt = 0;
	char *reten;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		lengt++;
	reten = malloc(sizeof(char) * (lengt + 1));
	if (!reten)
		return (NULL);
	for (lengt++; lengt--;)
		reten[lengt] = *--stri;
	return (reten);
}

/**
 * _putsin - prints an input string
 * @stri: the string to be printed
 *
 * Return: Nothing
 */
void _putsin(char *stri)
{
	int c = 0;

	if (!stri)
		return;
	while (stri[c] != '\0')
	{
		_putchar(stri[c]);
		c++;
	}
}

/**
 * _putchar - writes the character to stdout
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char a)
{
	static int c;
	static char mas[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || c >= WRITE_BUF_SIZE)
	{
		write(1, mas, c);
		c = 0;
	}
	if (a != BUF_FLUSH)
		mas[c++] = a;
	return (1);
}
