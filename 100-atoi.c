#include "shell.h"

/**
 * active - returns true if shell is active
 * @mes: struct address
 *
 * Return: 1 if active mode, 0 otherwise
 */

int active(mes_t *mes)
{
	return (isatty(STDIN_FILENO) && mes->readfd <= 2);
}

/**
 * unique_ch - checks if Character is unique that marks the start of stop
 * @u: the char to check
 * @unique: the string that marks the start or stop of statement
 * Return: 1 if true, 0 if false
 */

int unique_ch(char u, char *unique)
{
	while (*unique)
		if (*unique++ == u)
			return (1);
	return (0);
}

/**
 * alphabet - checks for alphabetical character
 * @a: The character to input
 * Return: 1 if a is alphabetic, 0 otherwise
 */

int alphabet(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @a: string to be converted
 *
 * Return: the int converted from the string, and 0 if unavailable 
 */
int _atoi(char *a)
{
	int b, c, d, e, g;
	unsigned int f;

	b = 0;
	c = 0;
	d = 0;
	e = 0;
	f = 0;
	g = 0;

	while (a[e] != '\0')
		e++;
	while (b < e && f == 0)
	{
		if (a[b] == '-')
			++c;
		if (a[b] >= '0' && a[b] <= '9')
		{
			g = a[b] - '0';
			if (c % 2)
				g = -g;
			d = d * 10 + g;
			f = 1;
			if (a[b + 1] < '0' || a[b + 1] > '9')
				break;
			f = 0;
		}
		b++;
	}
	if (f == 0)
		return (0);

	return (d);
}
