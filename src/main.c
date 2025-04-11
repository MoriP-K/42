/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/11 14:01:37 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	throw_error(char *cmd)
{
	printf("Error: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	init_ms(t_ms *ms, char *envp[], char *line, int is_first_init)
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	if (is_first_init)
		ms->envp = envp_dup(envp);
	else
		ms->envp = envp;
	init_lexer(&(ms->token), line);
	if (!ms->token)
		return;
	init_parser(&(ms->parse), ms->token);
	if (!ms->parse)
		return;
	init_env(&(ms->env), ms->envp);
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
	t_ms		ms;
	char 		*line;
	static char	**new_envp;
	static int	is_first_init = 1;

	(void)ac;
	(void)av;
	init_signal();
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break;
		if (*line == '\0')
			continue;
		add_history(line);
		if (is_first_init)
		{
			init_ms(&ms, envp, line, is_first_init);
			is_first_init = 0;
		}
		else
			init_ms(&ms, new_envp, line, is_first_init);
		if (ms.token == NULL || ms.parse == NULL)
			continue;
		do_exec(&ms, ms.parse);
		wait_child_process(&(ms).proc, ms.cl.cmd_count);
		// free_parser(ms.parse);
		new_envp = envp_dup(ms.envp);
		//free_old_envp(ms.envp); freeすると２回目以降壊れる
		free_ms(&ms);
	}
	if (new_envp != NULL)
		free_old_envp(new_envp);
	write(1, "exit\n", 5);
	return (0);
}
