/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:32 by masa              #+#    #+#             */
/*   Updated: 2025/04/12 12:39:14 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_ms *ms, size_t index)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, ms->fd.pipe[index][1]);
		write(ms->fd.pipe[index][1], "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
}