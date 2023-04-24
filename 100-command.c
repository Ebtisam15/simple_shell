#include "shell.h"

/**
 * exe_cmd - determines if a file is an executable command
 * @mes: the mes struct
 * @npath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int exe_cmd(mes_t *mes, char *npath)
{
	struct stat sti;

	(void)mes;
	if (!npath || stat(npath, &sti))
		return (0);

	if (sti.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @npathstr: the NPATH string
 * @starti: starting index
 * @stopi: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *npathstr, int starti, int stopi)
{
	static char m[1024];
	int l = 0, nk = 0;

	for (nk = 0, l = starti; l < stopi; l++)
		if (npathstr[l] != ':')
			m[nk++] = npathstr[l];
	m[nk] = 0;
	return (m);
}

/**
 * find_npath - finds this cmd in the NPATH string
 * @mes: the mes struct
 * @npathstr: the NPATH string
 * @cmdf: the cmd to find
 *
 * Return: full npath of cmd if found or NULL
 */
char *find_npath(mes_t *mes, char *npathstr, char *cmdf)
{
	int l = 0, curre_pos = 0;
	char *npath;

	if (!npathstr)
		return (NULL);
	if ((_strlen(cmdf) > 2) && needle_start_with(cmdf, "./"))
	{
		if (exe_cmd(mes, cmdf))
			return (cmdf);
	}
	while (1)
	{
		if (!npathstr[l] || npathstr[l] == ':')
		{
			npath = dup_chars(npathstr, curre_pos, l);
			if (!*npath)
				_strcat(npath, cmdf);
			else
			{
				_strcat(npath, "/");
				_strcat(npath, cmdf);
			}
			if (exe_cmd(mes, npath))
				return (npath);
			if (!npathstr[l])
				break;
			curre_pos = l;
		}
		l++;
	}
	return (NULL);
}
