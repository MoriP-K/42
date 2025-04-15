/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:12 by masa              #+#    #+#             */
/*   Updated: 2025/04/15 21:25:48 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_empty_token(t_token *next)
{
	t_token	*empty_token;

	empty_token = (t_token *)malloc(sizeof(t_token));
	empty_token->word = ft_strdup("");
	empty_token->kinds = TK_WORD;
	empty_token->next = next;
	return (empty_token);
}

void	conbine_adjacent_quotes(t_token *token)
{
	t_token	*temp_for_free;
	char	*temp_for_free2;

	temp_for_free = token->next;
	temp_for_free2 = token->word;
	token->word = ft_strjoin(token->word, token->next->word);
	free(temp_for_free->word);
	free(temp_for_free);
	free(temp_for_free2);
	token->next = token->next->next;
}

t_token	*integrate_quotes(t_token *token)
{
	t_token	*result;

	result = token;
	if (token->kinds == TK_META && (token->word[0] == '\"' || token->word[0] == '\''))
	{
		token = conbine_all(token);
		if (token->kinds == TK_EOF)
			return (get_empty_token(token));
		result = token;
		token = token->next;
	}
	while (token->kinds != TK_EOF)
	{
		if (token->next->kinds == TK_META && (token->next->word[0] == '\"' || token->next->word[0] == '\''))
			token->next = conbine_all(token->next);
		token = token->next;
	}
	token = result;
	while (token->kinds != TK_EOF)
	{
		while (token->kinds == TK_WORD && token->next->kinds == TK_WORD)
			conbine_adjacent_quotes(token);
		token = token->next;
	}
	return (result);
}
