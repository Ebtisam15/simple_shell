#include "shell.h"

/**
 * _sprint - writes the character k to stderr
 * @k: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _sprint(char k)
{
	static int l;
	static char m[WRITE_M_SIZE];

	if (k == M_FLUSH || l >= WRITE_M_SIZE)
	{
		write(2, m, l);
		l = 0;
	}
	if (k != M_FLUSH)
		m[l++] = k;
	return (1);
}

/**
 * sprint - prints an input string
 * @h: the string to be printed
 *
 * Return: Nothing
 */

void sprint(char *h)
{
	int j = 0;

	if (!h)
		return;
	while (h[j] != '\0')
	{
		_sprint(h[j]);
		j++;
	}
}

/**
 * _sprintfd - writes the character k to given fd
 * @k: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _sprintfd(char k, int fd)
{
	static int l;
	static char m[WRITE_M_SIZE];

	if (k == M_FLUSH || l >= WRITE_M_SIZE)
	{
		write(fd, m, l);
		l = 0;
	}
	if (k != M_FLUSH)
		m[l++] = k;
	return (1);
}

/**
 * _printsfd - prints an input string
 * @h: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _printsfd(char *h, int fd)
{
	int l = 0;

	if (!h)
		return (0);
	while (*h)
	{
		l += _sprintfd(*h++, fd);
	}
	return (l);
}
