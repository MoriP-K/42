/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:32:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 22:15:12 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_lexer(t_ms *ms, t_token **token, char *line)
{
	*token = tokenizer(ms, line);
	free(line);
}

// void	check_parser(t_parse *parse)
// {
// 	int		i;
// 	int j = 0;
// 	t_parse	*p = NULL;
// 	t_token	*t = NULL;

// 	p = parse;
// 	while (p)
// 	{
// 		i = 0;
// 		if (p->cmd)
// 			printf("--parse[%d]--\n", j++);
// 		if (p->cmd)
// 			printf("cmd: %s\n", p->cmd);
// 		if (p->args)
// 		{
// 			while (p->args[i])
// 			{
// 				printf("args[%d]: %s\n", i, p->args[i]);
// 				i++;
// 			}
// 		}
// 		t = p->token;
// 		if (p->token)
// 		{
// 			while (t)
// 			{
// 				printf("token->word: %s\n", t->word);
// 				t = t->next;
// 			}
// 		}
// 		if (p->infile)
// 			printf("infile: %s\n", p->infile);
// 		if (p->outfile)
// 			printf("outfile: %s\n", p->outfile);
// 		if (p->delimiter)
// 			printf("delimiter: %s\n", p->delimiter);
// 		write(1, "\n", 1);
// 		p = p->next;
// 	}
// }

void	init_parser(t_parse **parse, t_token *token, t_ms *ms)
{
	if (!token)
		return ;
	*parse = do_parse(token, ms);
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
