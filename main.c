#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * main - starting point of the program
 * @ac: argument count
 * @av: argument vector
 * Return: Returns 0 if successful, 1 on error
*/

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int ffd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (ffd)
			: "r" (ffd));

	if (ac == 2)
	{
		ffd = open(av[1], O_RDONLY);
		if (ffd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = ffd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
