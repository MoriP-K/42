/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:45 by motomo            #+#    #+#             */
/*   Updated: 2025/03/17 21:51:43 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *set_new_word(char *word)
{
		
}

t_token	*expand_env(t_token *token)
{
	int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->word[i] == '$' && token->word[i + 1])
			token->word = set_new_word(token->word);
	}
	return (token);
}

t_token	*expand_parse(t_token *token)
{
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_WORD)
			token = expand_env(token);
		token = token->next;
	}
}