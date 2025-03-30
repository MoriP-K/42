/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/30 22:23:20 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	throw_error(char *cmd)
{
	printf("Error: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	init_ms(t_ms *ms, char *envp[], char *line)
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	ms->envp = envp;
	init_lexer(&(ms->token), line);
	if (!ms->token)
		return;
	init_parser(&(ms->parse), ms->token);
	if (!ms->parse)
		return;
	init_env(&(ms->env), envp);
	init_exec(ms, ms->parse, &(ms->cl));
}

void	wait_child_process(t_proc *proc, size_t cmd_count)
{
	size_t	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(proc->id[i], &(proc)->status, 0);
		i++;
	}
}

int main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char *line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		add_history(line);
		init_ms(&ms, envp, line);
		if (ms.token == NULL || ms.parse == NULL)
			continue;
		do_exec(&ms, ms.parse);
		wait_child_process(&(ms).proc, ms.cl.cmd_count);
		// free_parser(ms.parse);
		free_ms(&ms);
	}
	write(1, "exit\n", 5);
	return (0);
}
