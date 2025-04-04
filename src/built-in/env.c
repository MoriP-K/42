/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:53:06 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 22:27:46 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_env(char **envp)
{
	size_t	i;

	// envp = NULL;
	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	if (!envp)
	{
		// TODO：perrorではなくenvpがNULLのときのエラー出力関数を作成する
		perror("env");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	// envp = NULL;
	my_env(envp);
}

