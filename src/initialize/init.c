/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:32:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/21 22:22:08 by kmoriyam         ###   ########.fr       */
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

void	init_parser(t_parse **parse, t_token *token, t_ms *ms)
{
	t_parse *first_parse;
	int		i;

	if (!token)
		return;
	*parse = do_parse(token, ms);
	first_parse = *parse;
	// int j = 0;
	while (*parse)
	{
		i = 0;
		// if (*parse)
		// 	printf("--parse[%d]--\n", j++);
		// if ((*parse)->cmd != NULL)
		// 	printf("cmd: %s\n", (*parse)->cmd);
		// if ((*parse)->args != NULL)
		// {
		// 	while ((*parse)->args[i])
		// 	{
		// 		printf("args[%d]: %s\n", i, (*parse)->args[i]);
		// 		i++;
		// 	}
		// 	write(1, "\n", 1);
		// }
		// if ((*parse)->token)
		// {
		// 	while ((*parse)->token)
		// 	{
		// 		printf("token->word: %s\n", (*parse)->token->word);
		// 		*parse = (*parse)->next;
		// 	}
		// 	write(1, "\n", 1);
		// }
		// if ((*parse)->infile != NULL)
		// 	printf("infile: %s\n", (*parse)->infile);
		// if ((*parse)->outfile != NULL)
		// 	printf("outfile: %s\n", (*parse)->outfile);
		// if ((*parse)->delimiter != NULL)
		// 	printf("delimiter: %s\n\n", (*parse)->delimiter);
		*parse = (*parse)->next;
	}
	*parse = first_parse;
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
