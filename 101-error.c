#include "shell.h"

/**
 * intatoi - converts a string to an integer
 * @a: the string to be converted
 * Return: 0 if no sbers in string, converted sber otherwise
 *       -1 on error
 */
int intatoi(char *a)
{
	int l = 0;
	unsigned long int f = 0;

	if (*a == '+')
		a++;  /* TODO: why does this make main return 255? */
	for (l = 0;  a[l] != '\0'; l++)
	{
		if (a[l] >= '0' && a[l] <= '9')
		{
			f *= 10;
			f += (a[l] - '0');
			if (f > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (f);
}

/**
 * intbase - function prints a decimal (integer) sber (base 10)
 * @o: the input
 * @fd: the filedescriptor to write to
 *
 * Return: sber of characters printed
 */
int intbase(int o, int fd)
{
	int (*__putchar)(char) = _putchar;
	int l, p = 0;
	unsigned int q, r;

	if (fd == STDERR_FILENO)
		__putchar = _sprint;
	if (o < 0)
	{
		q = -o;
		__putchar('-');
		p++;
	}
	else
		q = o;
	r = q;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (q / l)
		{
			__putchar('0' + r / l);
			p++;
		}
		r %= l;
	}
	__putchar('0' + r);
	p++;

	return (p);
}

/**
 * ermes - prints an error message
 * @mes: the parameter & return mes struct
 * @sh: string containing specified error type
 * Return: 0 if no sbers in string, converted sber otherwise
 *        -1 on error
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
 * confun - converter function
 * @s: sber
 * @u: base
 * @t: argument flags
 *
 * Return: string
 */
char *confun(long int s, int u, int t)
{
	static char *v;
	static char mb[50];
	char w = 0;
	char *x;
	unsigned long n = s;

	if (!(t & CONVERT_UNSIGNED) && s < 0)
	{
		n = -s;
		w = '-';

	}
	v = t & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	x = &mb[49];
	*x = '\0';

	do	{
		*--x = v[n % u];
		n /= u;
	} while (n != 0);

	if (w)
		*--x = w;
	return (x);
}

/**
 * funrep - function replaces first instance of '#' with '\0'
 * @m: address of the string to modify
 *
 * Return: Always 0;
 */
void funrep(char *m)
{
	int l;

	for (l = 0; m[l] != '\0'; l++)
		if (m[l] == '#' && (!l || m[l - 1] == ' '))
		{
			m[l] = '\0';
			break;
		}
}
