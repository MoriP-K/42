/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:00:31 by masa              #+#    #+#             */
/*   Updated: 2025/05/01 21:33:16 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exit_status(t_ms *ms)
{
	return (ft_itoa(ms->exit_status));
}

void	throw_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd);
	exit(EXIT_FAILURE);
}
