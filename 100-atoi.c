#include "shell.h"

/**
 * _active - returns true if shell is _active mode
 * @mes: struct address
 *
 * Return: 1 if _active mode, 0 otherwise
 */
int _active(mes_t *mes)
{
	return (isatty(STDIN_FILENO) && mes->readfd <= 2);
}

/**
 * is_delimeter - checks if character is starting or end of a unit data
 * @a: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char a, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == a)
			return (1);
	return (0);
}

/**
 * _isalphabet - checks for alphabetic character
 * @a: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphabet(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoistring - converts a string to an integer
 * @b: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoistring(char *b)
{
	int c, mark = 1, indi = 0, outcome;
	unsigned int product = 0;

	for (c = 0; b[c] != '\0' && indi != 2; c++)
	{
		if (b[c] == '-')
			mark *= -1;

		if (b[c] >= '0' && b[c] <= '9')
		{
			indi = 1;
			product *= 10;
			product += (b[c] - '0');
		}
		else if (indi == 1)
			indi = 2;
	}

	if (mark == -1)
		outcome = -product;
	else
		outcome = product;

	return (outcome);
}
