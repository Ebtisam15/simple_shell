#include "shell.h"

/**
 * intatoi - converts a string to an integer
 * @a: the string to be converted
 * Return: 0 if no string read, converted number otherwise -1 for error
 */
int intatoi(char *a)
{
	int l = 0;
	unsigned long int outcome = 0;

	if (*a == '+')
		a++;
	for (l = 0;  a[l] != '\0'; l++)
	{
		if (a[l] >= '0' && a[l] <= '9')
		{
			outcome *= 10;
			outcome += (a[l] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outcome);
}

/**
 * ermes - prints an error message
 * @mes: the parameter & return message struct
 * @sh: string containing specified error type
 * Return: Void
 */
void ermes(mes_t *mes, char *sh)
{
	sprint(mes->filen);
	sprint(": ");
	intbase(mes->count, STDERR_FILENO);
	sprint(": ");
	sprint(mes->argv[0]);
	sprint(": ");
	sprint(sh);
}

/**
 * intbase - function prints a decimal (integer) number (base 10)
 * @key_in: a decimal (integer) number (base 10)
 * @fd: the file descriptor
 *
 * Return: number of characters printed
 */
int intbase(int key_in, int fd)
{
	int (*_iputchar)(char) = _putchar;
	int l, num = 0;
	unsigned int base, cur;

	if (fd == STDERR_FILENO)
		_iputchar = _sprint;
	if (key_in < 0)
	{
		base = -key_in;
		_iputchar('-');
		num++;
	}
	else
		base = key_in;
	cur = base;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (base / l)
		{
			_iputchar('0' + cur / l);
			num++;
		}
		cur %= l;
	}
	_iputchar('0' + cur);
	num++;

	return (num);
}

/**
 * confun - converter function, a clone of atoi
 * @s: number
 * @u: base
 * @t: argument flags
 *
 * Return: string
 */
char *confun(long int s, int u, int t)
{
	static char *arr;
	static char atsa1[50];
	char mark = 0;
	char *x;
	unsigned long n = s;

	if (!(t & CONVERT_UNSIGNED) && s < 0)
	{
		n = -s;
		mark = '-';

	}
	arr = t & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	x = &atsa1[49];
	*x = '\0';

	do	{
		*--x = arr[n % u];
		n /= u;
	} while (n != 0);

	if (mark)
		*--x = mark;
	return (x);
}

/**
 * funrep - function replaces first instance of '#' with '\0'
 * @atsa: address of the string to modify
 *
 * Return: void.
 */
void funrep(char *atsa)
{
	int l;

	for (l = 0; atsa[l] != '\0'; l++)
		if (atsa[l] == '#' && (!l || atsa[l - 1] == ' '))
		{
			atsa[l] = '\0';
			break;
		}
}
