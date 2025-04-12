/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/11 23:24:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	throw_error(char *cmd)
{
	printf("Error: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	init_ms(t_ms *ms, char *envp[])
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	ms->envp = envp_dup(envp);
	init_env(&(ms->env), ms->envp);
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
	char 	*line;

	(void)ac;
	(void)av;
	init_ms(&ms, envp);
	init_signal();
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break;
		if (*line == '\0')
			continue;
		add_history(line);
		init_lexer(&(ms.token), line);
		if (!ms.token)
			return (0);
		init_parser(&(ms.parse), ms.token);
		if (!ms.parse)
			return (0);
		init_exec(&ms, ms.parse, &(ms.cl));
		if (ms.token == NULL || ms.parse == NULL)
			continue;
		do_exec(&ms, ms.parse);
		wait_child_process(&(ms).proc, ms.cl.cmd_count);
		free_ms(&ms);
	}
	free_env(&(ms.env));
	write(1, "exit\n", 5);
	return (0);
}
