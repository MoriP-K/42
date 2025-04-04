/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:32:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/03 21:53:23 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cl(t_cl *cl, t_parse *parse)
{
	t_parse *tmp;
	int		count;

	tmp = parse;
	count = 0;
	while (tmp)
	{
		if (tmp->cmd)
			count++;
		tmp = tmp->next;
	}
	printf("cmd count = %d\n\n", count);
	cl->cmd_count = count;
	cl->path = NULL;
}

void	init_proc(t_proc *proc, t_cl *cl)
{
	size_t	i;

	proc->id = malloc(sizeof(int) * cl->cmd_count);
	if (!proc->id)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < cl->cmd_count)
		proc->id[i++] = -1;
	proc->status = 0;
}

void	init_fd(t_fd *fd, t_cl *cl)
{
	size_t	i;

	fd->pipe = malloc(sizeof(int *) * cl->cmd_count);
	if (!fd->pipe)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fd->infile = -1;
	fd->outfile = - 1;
	i = 0;
	while (i < cl->cmd_count)
	{
		fd->pipe[i] = malloc(sizeof(int) * 2);
		if (!fd->pipe[i])
		{
			perror("malloc");
			free_fd(fd, cl);
			exit(EXIT_FAILURE);
		}
		fd->pipe[i][0] = -1;
		fd->pipe[i][1] = -1;
		i++;
	}
}

void	init_exec(t_ms *ms, t_parse *parse, t_cl *cl)
{
	init_cl(&(ms->cl), parse);
	init_proc(&(ms->proc), cl);
	init_fd(&(ms->fd), cl);
}

void	init_lexer(t_token **token, char *line)
{
	*token = tokenizer(line);
	while (*token)
	{
		printf("%s\n", (*token)->word);
		(*token) = (*token)->next;
	}
	free(line);
}

void	init_parser(t_parse **parse, t_token *token)
{
	t_parse *first_parse;
	int		i;

	*parse = do_parse(token);
	first_parse = *parse;
	while (*parse)
	{
		i = 0;
		if ((*parse)->cmd != NULL)
			printf("cmd :%s\n", (*parse)->cmd);
		// if ((*parse)->args != NULL)
		// {
		// 	while ((*parse)->args[i])
		// 	{
		// 		printf("args[%d] :%s\n", i, (*parse)->args[i]);
		// 		i++;
		// 	}
		// 	write(1, "\n", 1);
		// }
		first_parse->infile = NULL;
		first_parse->outfile = NULL;
		if ((*parse)->infile != NULL)
			printf("infile :%s\n", (*parse)->infile);
		if ((*parse)->outfile != NULL)
			printf("outfile :%s\n", (*parse)->outfile);
		*parse = (*parse)->next;
	}
	*parse = first_parse;
}

void	init_env(t_env **env, char *envp[])
{
	int		i;
	t_env	*new_env;

	i = 0;
	*env = NULL;
	while (envp[i])
	{
		new_env = new_env_lst();
		if (!new_env)
		{
			free_env(env);
			// throw_error();
			exit(EXIT_FAILURE);
		}
		new_env->key = get_env_key(envp[i]);
		new_env->value = get_env_value(envp[i]);
		add_env_lst(env, new_env);
		i++;
	}
}