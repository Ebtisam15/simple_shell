#include "shell.h"

/**
 * _printsti - prints an input string
 * @stri: the string to be printed
 *
 * Return: Nothing
 */
void _printsti(char *stri)
{
	int c = 0;

	if (!stri)
		return;
	while (stri[c] != '\0')
	{
		_eputchark(stri[c]);
		c++;
	}
}

/**
 * _eputchark - writes the character to stderr
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchark(char a)
{
	static int c;
	static char m[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || c >= WRITE_BUF_SIZE)
	{
		write(2, m, c);
		c = 0;
	}
	if (a != BUF_FLUSH)
		m[c++] = a;
	return (1);
}

/**
 * _putinfd - writes the character to given fd
 * @a: The character to print
 * @fd: The file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putinfd(char a, int fd)
{
	static int c;
	static char m[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || c >= WRITE_BUF_SIZE)
	{
		write(fd, m, c);
		c = 0;
	}
	if (a != BUF_FLUSH)
		m[c++] = a;
	return (1);
}

/**
 * _putsinfd - prints an input string
 * @stri: the string to be printed
 * @fd: the file descriptor
 *
 * Return: the number of chars put
 */
int _putsinfd(char *stri, int fd)
{
	int c = 0;

	if (!stri)
		return (0);
	while (*stri)
	{
		c += _putinfd(*stri++, fd);
	}
	return (c);
}
