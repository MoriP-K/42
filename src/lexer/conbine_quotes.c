/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conbine_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:23:48 by masa              #+#    #+#             */
/*   Updated: 2025/04/15 22:32:30 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotes_empty(t_token **result, t_token **token)
{
	*result = get_empty_token((*token)->next->next); 
	free((*token)->next->word);
	free((*token)->next);
	free((*token)->word);
	free(*token);
}

int	get_strcmp(t_token *token, t_token *start)
{
	return(ft_strcmp(token->word, start->word));
}

void	conbine_quotes(t_token **token, t_token **start, t_token **result)
{
	t_token	*tff;
	char	*temp_for_free2;
	
	while (!((*token)->kinds == TK_META && !get_strcmp(*token, *start)))
	{
		temp_for_free2 = (*result)->word;
		(*result)->word = ft_strjoin((*result)->word, (*token)->word);
		(*result)->next = (*token)->next;
		tff = (*token);
		(*token) = (*token)->next;
		free(tff->word);
		free(temp_for_free2);
		free(tff);
	}
	if ((*token)->kinds == TK_META 
			&& !ft_strcmp((*token)->word, (*start)->word))
		tff = (*token);
	(*result)->next = (*token)->next;
	if (tff->kinds == TK_META)
	{
		free(tff->word);
		free(tff);
	}
	free((*start)->word);
	free(*start);
}

t_token	*conbine_all(t_token *token)
{
	t_token	*result;
	t_token	*temp_for_free;
	t_token	*start_quate;
	
	start_quate = token;
	if (token->next->kinds == TK_META 
		&& ft_strcmp(token->next->word, start_quate->word) == 0)
	{
		quotes_empty(&result, &token);
		return (result);
	}
	result = (t_token *)malloc(sizeof(t_token));
	result->kinds = TK_WORD;
	if (ft_strcmp(token->word, "\'") == 0)
		result->quote = Q_SINGLE;
	else if (ft_strcmp(token->word, "\"") == 0)
		result->quote = Q_DOUBLE;
	token = token->next;
	result->word = ft_strdup(token->word);
	temp_for_free = token;
	token = token->next;
	free(temp_for_free->word);
	free(temp_for_free);
	conbine_quotes(&token, &start_quate, &result);
	return (result);
}
