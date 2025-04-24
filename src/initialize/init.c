/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:32:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/25 00:10:54 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cl(t_cl **cl, t_parse *parse, t_ms *ms)
{
	t_parse	*tmp;
	int		count;

	*cl = (t_cl *)ms_malloc(sizeof(t_cl), ms);
	tmp = parse;
	count = 0;
	while (tmp)
	{
		if (tmp->cmd || tmp->delimiter)
			count++;
		tmp = tmp->next;
	}
	(*cl)->cmd_count = count;
	(*cl)->path = NULL;
}

void	init_proc(t_proc **proc, t_cl *cl, t_ms *ms)
{
	size_t	i;

	*proc = (t_proc *)ms_malloc(sizeof(t_proc), ms);
	(*proc)->id = (pid_t *)ms_malloc(sizeof(pid_t) * cl->cmd_count, ms);
	i = 0;
	while (i < cl->cmd_count)
		(*proc)->id[i++] = -1;
	(*proc)->status = 0;
}

void	init_fd(t_fd **fd, t_cl *cl, t_ms *ms)
{
	size_t	i;

	*fd = (t_fd *)ms_malloc(sizeof(t_fd), ms);
	(*fd)->pipe = ms_malloc(sizeof(int *) * cl->cmd_count, ms);
	(*fd)->infile = -1;
	(*fd)->outfile = -1;
	(*fd)->tmp_in = -1;
	(*fd)->tmp_out = -1;
	(*fd)->here_doc = -1;
	i = 0;
	while (i < cl->cmd_count)
	{
		(*fd)->pipe[i] = ms_malloc(sizeof(int) * 2, ms);
		(*fd)->pipe[i][0] = -1;
		(*fd)->pipe[i][1] = -1;
		i++;
	}
}

void	init_exec(t_ms *ms, t_parse *parse)
{
	init_cl(&(ms->cl), parse, ms);
	init_proc(&(ms->proc), ms->cl, ms);
	init_fd(&(ms->fd), ms->cl, ms);
}

void	init_lexer(t_ms *ms, t_token **token, char *line)
{
	*token = tokenizer(ms, line);
	// t_token *tmp = *token;
	// while (tmp)
	// {
	// 	printf("word: %s, kind: %d\n", tmp->word, tmp->kinds);
	// 	tmp = tmp->next;
	// }
	free(line);
}

void	check_parser(t_parse *parse)
{
	int		i;
	int j = 0;
	t_parse	*p = NULL;
	t_token	*t = NULL;

	p = parse;
	while (p)
	{
		i = 0;
		if (p->cmd)
			printf("--parse[%d]--\n", j++);
		if (p->cmd)
			printf("cmd: %s\n", p->cmd);
		if (p->args)
		{
			while (p->args[i])
			{
				printf("args[%d]: %s\n", i, p->args[i]);
				i++;
			}
		}
		t = p->token;
		if (p->token)
		{
			while (t)
			{
				printf("token->word: %s\n", t->word);
				t = t->next;
			}
		}
		if (p->infile)
			printf("infile: %s\n", p->infile);
		if (p->outfile)
			printf("outfile: %s\n", p->outfile);
		if (p->delimiter)
			printf("delimiter: %s\n", p->delimiter);
		write(1, "\n", 1);
		p = p->next;
	}
}

void	init_parser(t_parse **parse, t_token *token, t_ms *ms)
{
	if (!token)
		return;
	*parse = do_parse(token, ms);
	check_parser(*parse);
}

void	init_env(t_env **env, char *envp[], t_ms *ms)
{
	int		i;
	t_env	*new_env;

	i = 0;
	*env = NULL;
	while (envp[i])
	{
		new_env = new_env_lst(ms);
		new_env->key = get_env_key(envp[i], ms);
		new_env->value = get_env_value(envp[i], ms);
		add_env_lst(env, new_env);
		i++;
	}
}
