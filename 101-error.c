#include "shell.h"

/**
 * _erroratoi - converts a string to an integer
 * @b: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erroratoi(char *b)
{
	int c = 0;
	unsigned long int product = 0;

	if (*b == '+')
		b++;
	for (c = 0;  b[c] != '\0'; c++)
	{
		if (b[c] >= '0' && b[c] <= '9')
		{
			product *= 10;
			product += (b[c] - '0');
			if (product > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (product);
}

/**
 * errprint - prints an error message
 * @mes: the parameter & return info struct
 * @stris: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void errprint(mes_t *mes, char *stris)
{
	_printsti(mes->fnamed);
	_printsti(": ");
	print_base(mes->lines_count, STDERR_FILENO);
	_printsti(": ");
	_printsti(mes->argv[0]);
	_printsti(": ");
	_printsti(stris);
}

/**
 * print_base - function prints a decimal (integer) number (base 10)
 * @key_in: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_base(int key_in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int c, counts = 0;
	unsigned int base, currents;

	if (fd == STDERR_FILENO)
		__putchar = _eputchark;
	if (key_in < 0)
	{
		base = -key_in;
		__putchar('-');
		counts++;
	}
	else
		base = key_in;
	currents = base;
	for (c = 1000000000; c > 1; c /= 10)
	{
		if (base / c)
		{
			__putchar('0' + currents / c);
			counts++;
		}
		currents %= c;
	}
	__putchar('0' + currents);
	counts++;

	return (counts);
}

/**
 * number_atoi - converter function, a clone of atoi
 * @num: number
 * @base: base
 * @flag: argument flags
 *
 * Return: string
 */
char *number_atoi(long int num, int base, int flag)
{
	static char *array;
	static char m[50];
	char mark = 0;
	char *ptri;
	unsigned long f = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		f = -num;
		mark = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptri = &m[49];
	*ptri = '\0';

	do	{
		*--ptri = array[f % base];
		f /= base;
	} while (f != 0);

	if (mark)
		*--ptri = mark;
	return (ptri);
}

/**
 * func_replace - function replaces first instance of '#' with '\0'
 * @mas: address of the string to modify
 *
 * Return: Always 0;
 */
void func_replace(char *mas)
{
	int c;

	for (c = 0; mas[c] != '\0'; c++)
		if (mas[c] == '#' && (!c || mas[c - 1] == ' '))
		{
			mas[c] = '\0';
			break;
		}
}
