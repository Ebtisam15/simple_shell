#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	mes_t mes[] = { MESS_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				sprint(av[0]);
				sprint(": 0: Can't open ");
				sprint(av[1]);
				_sprint('\n');
				_sprint(M_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		mes->readfd = fd;
	}
	calculate_env_list(mes);
	read_nhistory(mes);
	hsh(mes, av);
	return (EXIT_SUCCESS);
}
