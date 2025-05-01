/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:12 by masa              #+#    #+#             */
/*   Updated: 2025/05/01 20:54:59 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_empty_token(t_token *next, t_ms *ms)
{
	t_token	*empty_token;

	empty_token = (t_token *)ms_malloc(sizeof(t_token), ms);
	empty_token->word = ms_strdup("", ms);
	empty_token->kinds = TK_WORD;
	empty_token->next = next;
	return (empty_token);
}

void	combine_adjacent_quotes(t_token **token, t_ms *ms)
{
	t_token	*temp_for_free;
	char	*temp_for_free2;

	while ((*token)->kinds != TK_EOF)
	{
		while ((*token)->kinds == TK_WORD && (*token)->next->kinds == TK_WORD)
		{
			temp_for_free = (*token)->next;
			temp_for_free2 = (*token)->word;
			(*token)->word
				= ms_strjoin((*token)->word, (*token)->next->word, ms);
			free(temp_for_free->word);
			free(temp_for_free);
			free(temp_for_free2);
			(*token)->next = (*token)->next->next;
		}
		(*token) = (*token)->next;
	}
}

void	set_garbage_token(t_token **garbage, t_token **result, t_token **token,
					t_ms *ms)
{
	*garbage = malloc(sizeof(t_token));
	(*garbage)->kinds = TK_WORD;
	(*garbage)->word = ms_strdup("a", ms);
	(*garbage)->next = (*token);
	(*token) = (*garbage);
	(*result) = (*token);
}

void	free_garbage(t_token **result, t_token **token)
{
	t_token	*tmp_token2;

	tmp_token2 = (*result);
	(*result) = (*result)->next;
	(*token) = (*result);
	free(tmp_token2->word);
	free(tmp_token2);
}

t_token	*integrate_quotes(t_token *token, t_ms *ms)
{
	t_token	*result;
	t_token	*tmp_token;

	set_garbage_token(&tmp_token, &result, &token, ms);
	if (token->kinds == TK_META && (token->word[0] == '\"'
			|| token->word[0] == '\''))
	{
		token = combine_all(token, ms);
		if (token->kinds == TK_EOF)
			return (get_empty_token(token, ms));
		result = token;
		token = token->next;
	}
	while (token->kinds != TK_EOF)
	{
		if (token->next->kinds == TK_META
			&& (token->next->word[0] == '\"' || token->next->word[0] == '\''))
			token->next = combine_all(token->next, ms);
		token = token->next;
	}
	free_garbage(&result, &token);
	combine_adjacent_quotes(&token, ms);
	return (result);
}
