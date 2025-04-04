/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:09:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/01 22:10:25 by kmoriyam         ###   ########.fr       */
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
	exit(EXIT_SUCCESS);
}
