/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:46:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 22:27:29 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#ifndef INIT_BUFSIZE
# define INIT_BUFSIZE 8192
#endif

int	main(int ac, char *av[])
{
	char	*home;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		free((char *)cwd);
		exit(EXIT_FAILURE);
	}
	if (ac == 1)
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("getenv");
			free((char *)cwd);
			exit (EXIT_FAILURE);
		}
		if (access(home, R_OK) == -1)
		{
			perror("access");
			free((char *)cwd);
			exit (EXIT_FAILURE);
		}
		if (chdir(home) == -1)
		{
			perror("chdir");
			free((char *)cwd);
			exit (EXIT_FAILURE);
		}
		printf("%s\n", getcwd(NULL, 0));
		free((char *)cwd);
		return (0);
	}
	else if (av[1])
	{
		if (chdir(av[1]) == -1)
		{
			perror("cd");
			free((char *)cwd);
			exit (EXIT_FAILURE);
		}
		printf("%s\n", getcwd(NULL, 0));
		free((char *)cwd);
		return (0);
	}
	printf("%s\n", getcwd(NULL, 0));
	free((char *)cwd);
	return (0);
}

