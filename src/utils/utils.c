/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:00:31 by masa              #+#    #+#             */
/*   Updated: 2025/05/01 20:58:13 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exit_status(t_ms *ms)
{
	return (ft_itoa(ms->exit_status));
}

void	throw_error(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	perror(cmd);
	exit(EXIT_FAILURE);
}
