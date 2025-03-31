/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:09:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 22:28:03 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = getenv("PWD");
		if (!pwd)
		{
			perror("pwd");
			exit (EXIT_FAILURE);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
}

int	main(int ac, char *av[], char *envp[])
{
	ft_pwd();
}