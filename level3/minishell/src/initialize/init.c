/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:32:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/01 21:32:30 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_lexer(t_ms *ms, t_token **token, char *line)
{
	*token = tokenizer(ms, line);
	free(line);
}

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
