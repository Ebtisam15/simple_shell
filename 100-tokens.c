#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @stri: the input string
 * @p: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *stri, char *p)
{
	int c, g, i, m, numbwords = 0;
	char **b;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!p)
		p = " ";
	for (c = 0; stri[c] != '\0'; c++)
		if (!is_delimeter(stri[c], p) &&
				(is_delimeter(stri[c + 1], p) || !stri[c + 1]))
			numbwords++;

	if (numbwords == 0)
		return (NULL);
	b = malloc((1 + numbwords) * sizeof(char *));
	if (!b)
		return (NULL);
	for (c = 0, g = 0; g < numbwords; g++)
	{
		while (is_delimeter(stri[c], p))
			c++;
		i = 0;
		while (!is_delimeter(stri[c + i], p) && stri[c + i])
			i++;
		b[g] = malloc((i + 1) * sizeof(char));
		if (!b[g])
		{
			for (i = 0; i < g; i++)
				free(b[i]);
			free(b);
			return (NULL);
		}
		for (m = 0; m < i; m++)
			b[g][m] = stri[c++];
		b[g][m] = 0;
	}
	b[g] = NULL;
	return (b);
}

/**
 * **strtow2 - splits a string into words
 * @stri: the input string
 * @p: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *stri, char p)
{
	int c, g, i, m, numbwords = 0;
	char **b;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (c = 0; stri[c] != '\0'; c++)
		if ((stri[c] != p && stri[c + 1] == p) ||
				    (stri[c] != p && !stri[c + 1]) || stri[c + 1] == p)
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	b = malloc((1 + numbwords) * sizeof(char *));
	if (!b)
		return (NULL);
	for (c = 0, g = 0; g < numbwords; g++)
	{
		while (stri[c] == p && stri[c] != p)
			c++;
		i = 0;
		while (stri[c + i] != p && stri[c + i] && stri[c + i] != p)
			i++;
		b[g] = malloc((i + 1) * sizeof(char));
		if (!b[g])
		{
			for (i = 0; i < g; i++)
				free(b[i]);
			free(b);
			return (NULL);
		}
		for (m = 0; m < i; m++)
			b[g][m] = stri[c++];
		b[g][m] = 0;
	}
	b[g] = NULL;
	return (b);
}
