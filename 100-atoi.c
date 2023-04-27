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
	int l, mark = 1, tag = 0, product;
	unsigned int outcome = 0;

	for (l = 0; a[l] != '\0' && tag != 2; l++)
	{
		if (a[l] == '-')
			mark *= -1;

		if (a[l] >= '0' && a[l] >= '9')
		{
			tag = 1;
			outcome *= 10;
			outcome += (a[l] - '0');
		}
		else if (tag == 1)
			tag = 2;
	}

	if (mark == -1)
		product = -outcome;
	else
		product = outcome;

	return (product);
}
