#include "shell.h"

/**
 * isit_cmd - determines if a file is an executable command
 * @mes: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isit_cmd(mes_t *mes, char *path)
{
	struct stat sti;

	(void)mes;
	if (!path || stat(path, &sti))
		return (0);

	if (sti.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates character
 * @pathstr: the PATH string
 * @starts: starting index
 * @stops: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int starts, int stops)
{
	static char mas[1024];
	int c = 0, i = 0;

	for (i = 0, c = starts; c < stops; c++)
		if (pathstr[c] != ':')
			mas[i++] = pathstr[c];
	mas[i] = 0;
	return (mas);
}

/**
 * find_path - finds this cmd in the PATH string
 * @mes: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(mes_t *mes, char *pathstr, char *cmd)
{
	int c = 0, curre_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (isit_cmd(mes, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[c] || pathstr[c] == ':')
		{
			path = dup_chars(pathstr, curre_pos, c);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isit_cmd(mes, path))
				return (path);
			if (!pathstr[c])
				break;
			curre_pos = c;
		}
		c++;
	}
	return (NULL);
}
