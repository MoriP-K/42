#include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int parse_args(t_ping *ping, int ac, char *av[])
{
	int opt;

	if (ac < 2)
	{
		arg_error();
	}
	else
	{
		while ((opt = getopt(ac, av, "v?")) != -1)
		{
			switch (opt) {
			case 'v':
				printf("arg: -v\n");
				ping->verbose = 1;
				break;
			case '?':
				print_help();
				exit(0);
				// return (1
				// break;
			default:
				printf("default\n");
				break;
			}
		}
		ping->hostname = av[optind];
	}

	return (0);
}