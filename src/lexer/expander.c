/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:45 by motomo            #+#    #+#             */
/*   Updated: 2025/04/15 21:05:17 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expand_env(t_ms *ms, t_token *token)
{
	int		i;
	char	*temp;

	i = 0;
	while (token->word[i])
	{
		if (token->word[i] == '$' && token->word[i + 1])
		{
			temp = token->word;
			if (ft_strcmp(token->word, "$?") == 0)
				token->word = get_exit_status(ms);
			else
				token->word = expand_join(ms, token->word);
			free(temp);
			i = -1;
		}
		i++;
	}
	return (token);
}

void	expand_token(t_ms *ms, t_token *token)
{
	size_t	in_single_quote;
	size_t	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_META && token->word[0] == '\'')
		{
			if (!in_double_quote)
				in_single_quote = !in_single_quote;
			else
				token->kinds = TK_WORD;
		}
		else if (token->kinds == TK_META && token->word[0] == '\"')
		{	
			if (!in_single_quote)
				in_double_quote = !in_double_quote;
			else
				token->kinds = TK_WORD;
		}
		if (token->kinds == TK_WORD && (!in_single_quote || in_double_quote))
			token = expand_env(ms, token);
		token = token->next;
	}
}
