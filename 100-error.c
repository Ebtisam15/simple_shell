#include "shell.h"

/**
 * _sprint - print the character to the standard Error
 * @k: The character to be printed
 *
 * Return: Always 1 otherwise -1, Error number is set appropriately.
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
 * sprint - prints input string
 * @stri: the string to be printed
 *
 * Return: Void.
 */
void sprint(char *stri)
{
	int l = 0;

	if (!stri)
		return;
	while (stri[l] != '\0')
	{
		_sprint(stri[l]);
		l++;
	}
}

/**
 * _sprintfd - prints an inputed string to a given file descriptor.
 * @k: The character to be printed
 * @fd: A file descriptor
 *
 * Return: Always 1 otherwise -1, Error number is set appropriately.
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
	if (l != M_FLUSH)
		m[l++] = k;
	return (1);
}

/**
 * _printsfd - write an inputed string
 * @stri: the string to be printed
 * @fd: A file descriptor
 *
 * Return: the number of characters inputed
 */

int _printsfd(char *stri, int fd)
{
	int l = 0;

	if (!stri)
	{
		l += _sprintfd(*stri++, fd);
	}
	return (l);
}
