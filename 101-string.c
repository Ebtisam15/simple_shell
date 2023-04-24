#include "shell.h"

/**
 * **string_into - splits a string into words. Repeat delimiters are ignored
 * @stri: the input string
 * @ds: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_into(char *stri, char *ds)
{
	int l, w, x, y, z = 0;
	char **a;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!ds)
		ds = " ";
	for (l = 0; stri[l] != '\0'; l++)
		if (!unique_ch(stri[l], ds) && (unique_ch(stri[l + 1], ds) || !stri[l + 1]))
			z++;

	if (z == 0)
		return (NULL);
	a = malloc((1 + z) * sizeof(char *));
	if (!a)
		return (NULL);
	for (l = 0, w = 0; w < z; w++)
	{
		while (unique_ch(stri[l], ds))
			l++;
		x = 0;
		while (!unique_ch(stri[l + x], ds) && stri[l + x])
			x++;
		a[w] = malloc((x + 1) * sizeof(char));
		if (!a[w])
		{
			for (x = 0; x < w; x++)
				free(a[x]);
			free(a);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			a[w][y] = stri[l++];
		a[w][y] = 0;
	}
	a[w] = NULL;
	return (a);
}

/**
 * **string_into2 - splits a string into words
 * @stri: the input string
 * @ds: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **string_into2(char *stri, char ds)
{
	int l, w, x, y, z = 0;
	char **a;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (l = 0; stri[l] != '\0'; l++)
		if ((stri[l] != ds && stri[l + 1] == ds) ||
				    (stri[l] != ds && !stri[l + 1]) || stri[l + 1] == ds)
			z++;
	if (z == 0)
		return (NULL);
	a = malloc((1 + z) * sizeof(char *));
	if (!a)
		return (NULL);
	for (l = 0, w = 0; w < z; w++)
	{
		while (stri[l] == ds && stri[l] != ds)
			l++;
		x = 0;
		while (stri[l + x] != ds && stri[l + x] && stri[l + x] != ds)
			x++;
		a[w] = malloc((x + 1) * sizeof(char));
		if (!a[x])
		{
			for (x = 0; x < w; x++)
				free(a[x]);
			free(a);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			a[w][y] = stri[l++];
		a[w][y] = 0;
	}
	a[y] = NULL;
	return (a);
}
