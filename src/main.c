/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:44:32 by motomo            #+#    #+#             */
/*   Updated: 2025/05/01 20:59:24 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ms(t_ms *ms, char *envp[])
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	ms->cl = NULL;
	ms->fd = NULL;
	ms->proc = NULL;
	ms->exit_status = 0;
	ms->envp = NULL;
	ms->envp = envp_dup(envp, ms);
	init_env(&(ms->env), ms->envp, ms);
}

void	wait_child_process(t_ms *ms, t_proc *proc, size_t cmd_count)
{
	size_t	i;

	i = 0;
	if (ms->cl->cmd_count == 1 && check_builtin_cmd(ms->parse->cmd))
		return ;
	while (i < cmd_count)
	{
		waitpid(proc->id[i], &(proc)->status, 0);
		if (WIFEXITED(proc->status))
			ms->exit_status = WEXITSTATUS(proc->status);
		else if (WIFSIGNALED(proc->status))
		{
			ms->exit_status = 128 + WTERMSIG(proc->status);
			if (ms->exit_status == 131)
				write(1, "Quit (core dumped)", 18);
			write(1, "\n", 1);
		}
		i++;
	}
}

void	sigint_check(t_ms *ms)
{
	if (g_sigint_received == 1)
		ms->exit_status = 130;
	g_sigint_received = 0;
	set_sigint_ign();
}

void	do_minishell(t_ms *ms, char *line)
{
	while (1)
	{
		set_sigint_redisplay();
		line = readline("minishell$ ");
		sigint_check(ms);
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		init_lexer(ms, &(ms->token), line);
		init_parser(&(ms->parse), ms->token, ms);
		if (!ms->token || !ms->parse)
			continue ;
		init_exec(ms, ms->parse);
		if (do_exec(ms, ms->parse))
			wait_child_process(ms, ms->proc, ms->cl->cmd_count);
		close_all_fds(ms->fd, ms->parse, ms->cl->cmd_count);
		free_ms(ms);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char	*line;

	(void)av;
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	init_ms(&ms, envp);
	do_minishell(&ms, line);
	ac = ms.exit_status;
	free_old_envp(ms.envp);
	free_env(&(ms.env));
	write(1, "exit\n", 5);
	return (ac);
}
