/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:45 by motomo            #+#    #+#             */
/*   Updated: 2025/04/15 16:55:54 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expand_env(t_ms *ms, t_token *token)
{
	int		i;
	int		has_dollor;
	char	*temp;

	i = 0;
	has_dollor = 0;
	temp = token->word;
	while (token->word[i])
	{
		if (token->word[i] == '$' && token->word[i + 1])
		{
			if (ft_strcmp(token->word, "$?") == 0)
				token->word = get_exit_status(ms);
			else
				token->word = expand_join(ms, token->word);
			i = -1;
			has_dollor = 1;
		}
		i++;
	}
	if (has_dollor == 1)
		free(temp);
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
		if (token->kinds == TK_WORD && token->single_quote != 1 && (!in_single_quote || in_double_quote))
			token = expand_env(ms, token);
		token = token->next;
	}
}
