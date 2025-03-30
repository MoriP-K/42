/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:27:27 by motomo            #+#    #+#             */
/*   Updated: 2025/03/30 16:57:29 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(t_token *token)
{
	if (token->word == NULL || !*(token->word))
		write(1, "minishell: syntax error near unexpected token `newline'\n", 56);
	else
	{
		write(1, "minishell: syntax error near unexpected token `", 47);
		write(1, token->word, ft_strlen(token->word));
		write(1, "\'\n", 2);
	}
}

int	check_quote_count(t_token *token)
{
	int	double_quote_count;
	int	single_quote_count;
	
	double_quote_count = 0;
	single_quote_count = 0;
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_META && token->word[0] == '\"')
			double_quote_count++;
		if (token->kinds == TK_META && token->word[0] == '\'')
			single_quote_count++;
		token = token->next;
	}
	if (double_quote_count % 2 == 1 || single_quote_count % 2 == 1)
	{
		print_error(token);
		return(0);
	}
	return(1);
}

int	pipe_error(t_token *token)
{
	token = token->next;
	if (token->kinds == TK_WORD)
	{
		return (1);
	}
	print_error(token);
	return (0);
}

int	redirect_error(t_token *token)
{
	token = token->next;
	if (token->kinds == TK_WORD)
		return (1);
	print_error(token);
	return (0);
}

int	syntax_error_handler(t_token *token)
{
	if (token->kinds == TK_META && token->word[0] == '|')
	{
		print_error(token);
		return (0);
	}
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_META && token->word[0] == '|')
		{
			if (!pipe_error(token))
				return (0);
		}
		if (token->kinds == TK_META 
			&& (token->word[0] == '>' || token->word[0] == '<'))
		{
			if (!redirect_error(token))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
