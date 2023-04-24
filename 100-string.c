#include "shell.h"

/**
 * needle_start_with - checks if needle starts with haystack
 * @hays: string to search
 * @needs: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *needle_start_with(const char *hays, const char *needs)
{
	while (*needs)
		if (*needs++ != *hays++)
			return (NULL);
	return ((char *)hays);
}

/**
 * dup_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *dup_string(const char *stri)
{
	int l = 0;
	char *r;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--stri;
	return (r);
}

/**
 * _instr - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _instr(char *stri)
{
	int l = 0;

	if (!stri)
		return;
	while (stri[l] != '\0')
	{
		_putchar(stri[l]);
		l++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char d)
{
	static int l;
	static char m[WRITE_M_SIZE];

	if (d == M_FLUSH || l >= WRITE_M_SIZE)
	{
		write(1, m, l);
		l = 0;
	}
	if (d != M_FLUSH)
		m[l++] = d;
	return (1);
}
