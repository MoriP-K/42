/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:12 by masa              #+#    #+#             */
/*   Updated: 2025/04/15 19:29:38 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*culling_space(t_token *token)
{
	t_token *first_token;
	t_token *temp;
	t_token	*temp2;
	
	while (token->kinds == TK_SPACE && token->kinds != TK_EOF)
	{
		temp = token;
		token = token->next;
		free(temp->word);
		free(temp);
	}
	first_token = token;
	temp = token;
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_SPACE)
		{
			while (token->kinds == TK_SPACE && token->kinds != TK_EOF)
			{
				temp2 = token;
				token = token->next;
				free(temp2->word);
				free(temp2);
			}
			temp->next = token;
		}
		temp = token;
		if (token->kinds != TK_EOF)
			token = token->next;
	}
	return (first_token);
}

t_token	*get_empty_token(t_token *next)
{
	t_token	*empty_token;

	empty_token = (t_token *)malloc(sizeof(t_token));
	empty_token->word = ft_strdup("");
	empty_token->kinds = TK_WORD;
	empty_token->next = next;
	return (empty_token);
}

t_token	*conbine_all(t_token *token)
{
	t_token	*result;
	t_token	*temp_for_free;
	char	*temp_for_free2;
	t_token	*start_quate;
	
	start_quate = token;
	if (token->next->kinds == TK_META && ft_strcmp(token->next->word, start_quate->word) == 0)
	{
		result = get_empty_token(token->next->next); 
		free(token->next->word);
		free(token->next);
		free(token->word);
		free(token);
		return (result);
	}
	else
	{
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
		while (!(token->kinds == TK_META && ft_strcmp(token->word, start_quate->word) == 0) && token->kinds != TK_EOF)
		{
			temp_for_free2 = result->word;
			result->word = ft_strjoin(result->word, token->word);
			result->next = token->next;
			temp_for_free = token;
			token = token->next;
			free(temp_for_free->word);
			free(temp_for_free2);
			free(temp_for_free);
		}
		if (token->kinds == TK_META && ft_strcmp(token->word, start_quate->word) == 0)
			temp_for_free = token;
		result->next = token->next;
		if (temp_for_free->kinds == TK_META)
		{
			free(temp_for_free->word);
			free(temp_for_free);
		}
		free(start_quate->word);
		free(start_quate);
	}
	return (result);
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
