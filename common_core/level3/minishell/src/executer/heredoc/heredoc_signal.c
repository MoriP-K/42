/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:17:50 by motomo            #+#    #+#             */
/*   Updated: 2025/05/01 21:18:22 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	heredoc_int_handler(int signo)
{
	int	devnull;

	(void)signo;
	write(1, "\n", 1);
	g_sigint_received = 1;
	rl_replace_line("", 0);
	devnull = open("/dev/null", O_RDONLY);
	if (devnull >= 0)
		dup2(devnull, STDIN_FILENO);
}

void	set_heredoc_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_int_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
