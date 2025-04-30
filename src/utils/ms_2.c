/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:53:21 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:58:57 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_dup(int fd, t_ms *ms)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd < 0)
	{
		throw_error("dup");
		free_ms(ms);
		exit(EXIT_FAILURE);
	}
	return (new_fd);
}

void	ms_dup2(int fd_1, int fd_2, t_ms *ms)
{
	if (dup2(fd_1, fd_2) == -1)
	{
		throw_error("dup2");
		free_ms(ms);
		exit(EXIT_FAILURE);
	}
}

int	ms_open(char *file, int flag, t_ms *ms)
{
	int	fd;

	fd = open(file, flag);
	if (fd < 0)
	{
		throw_error("open");
		free_ms(ms);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ms_open_mode(char *file, int flag, int permission, t_ms *ms)
{
	int	fd;

	fd = open(file, flag, permission);
	if (fd < 0)
	{
		throw_error("open");
		free_ms(ms);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
