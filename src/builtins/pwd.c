/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:32 by masa              #+#    #+#             */
/*   Updated: 2025/04/14 14:54:25 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_ms *ms, size_t index)
{
	char	*cwd;
	(void)index;
	(void)ms;
	
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		free(cwd);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return(0);
}