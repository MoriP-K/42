/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:27:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 22:27:40 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *av[])
{
	int	i;

	i = 0;
	if (!av[1])
	{
		printf("\n");
		return ;
	}
	if (av[1][i] == '-')
	{
		i++;
		while (av[1][i] == 'n')
			i++;
		if (!av[1][i])
		{
			if (av[2])
				printf("%s", av[2]);
			else
				printf("");
		}
		else
			printf("%s\n", av[1]);
	}
	else
		printf("%s\n", av[1]);
}

int	main(int ac, char *av[])
{
	(void)ac;
	ft_echo(av);
}

// case
// echo -nnnnn- test