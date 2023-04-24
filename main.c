#include "shell.h"

/**
 * main - entry point
 * @acount: arg count
 * @ave: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int acount, char **ave)
{
	mes_t mes[] = { MESS_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (acount == 2)
	{
		fd = open(ave[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				sprint(ave[0]);
				sprint(": 0: Can't open ");
				sprint(ave[1]);
				_sprint('\n');
				_sprint(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		mes->readfd = fd;
	}
	calculate_env_list(mes);
	read_nhistory(mes);
	hsh(mes, ave);
	return (EXIT_SUCCESS);
}
