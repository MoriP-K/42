/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/18 14:41:36 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	throw_error(char *cmd)
{
	// dprintf(2, "Error: %s\n", cmd);
	printf("Error: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	init_ms(t_ms *ms, char *envp[])
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	ms->cl.path = NULL;
	ms->fd.pipe = NULL;
	ms->proc.id = NULL;
	ms->exit_status = 0;
	ms->envp = NULL;
	ms->envp = envp_dup(envp, ms);
	init_env(&(ms->env), ms->envp, ms);
}

void	wait_child_process(t_ms *ms, t_proc *proc, size_t cmd_count)
{
	size_t	i;

	i = 0;
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

int main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char 	*line;

	(void)av;
	signal(SIGQUIT, SIG_IGN);
	init_ms(&ms, envp);
	while (1)
	{
		set_sigint_redisplay();
		line = readline("minishell > ");
		set_sigint_ign();
		if (!line)
			break;
		if (*line == '\0')
			continue;
		add_history(line);
		init_lexer(&ms, &(ms.token), line);
		init_parser(&(ms.parse), ms.token, &ms);
		if (!ms.token || !ms.parse)
			continue;
		//
		//t_parse *temp = ms.parse;
		// while (temp->cmd)
		// {
		// 	printf("cmd %s, infile %s, outfile %s, delimiter %s, append %d\n", temp->cmd, temp->infile, temp->outfile, temp->delimiter, temp->append);
		// 	int k = 0;
		// 	while (temp->args[k])
		// 	{
		// 		printf("args[%d] %s\n", k, temp->args[k]);
		// 		k++;
		// 	}
		// 	temp = temp->next;
		// }
		//
		init_exec(&ms, ms.parse, &(ms.cl));
		// if (ms.token == NULL || ms.parse == NULL)
		// 	continue;
		if (do_exec(&ms, ms.parse))
			wait_child_process(&ms, &(ms).proc, ms.cl.cmd_count);
		close_all_fds(&(ms.fd), ms.cl.cmd_count);
		free_ms(&ms);
	}
	ac = ms.exit_status;
	free_old_envp(ms.envp);
	free_env(&(ms.env));
	write(1, "exit\n", 5);
	return (ac);
}
