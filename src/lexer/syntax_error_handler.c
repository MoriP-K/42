/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:27:27 by motomo            #+#    #+#             */
/*   Updated: 2025/05/01 00:05:27 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_syntax_error(t_token *token)
{
	if (token->word == NULL || !*(token->word))
		write(1, "minishell: syntax error near unexpected token `newline'\n",
			61);
	else
	{
		write(1, "minishell: syntax error near unexpected token `", 52);
		write(1, token->word, ft_strlen(token->word));
		write(1, "\'\n", 2);
	}
}

int	pipe_error(t_token *token, t_token *first_token)
{
	token = token->next;
	if (token->kinds == TK_WORD)
	{
		return (1);
	}
	print_syntax_error(token);
	free_tokens(first_token);
	first_token = NULL;
	return (0);
}

int	redirect_error(t_token *token, t_token *first_token)
{
	token = token->next;
	if (token->kinds == TK_WORD)
		return (1);
	print_syntax_error(token);
	free_tokens(first_token);
	first_token = NULL;
	return (0);
}

int	syntax_error_handler(t_token *token)
{
	t_token	*first_token;

	first_token = token;
	if (token->kinds == TK_PIPE)
	{
		print_syntax_error(token);
		return (0);
	}
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_PIPE)
		{
			if (!pipe_error(token, first_token))
				return (0);
		}
		if (token->kinds == TK_APPEND || token->kinds == TK_HEREDOC
			|| token->kinds == TK_IN_REDIRECT
			|| token->kinds == TK_OUT_REDIRECT)
		{
			if (!redirect_error(token, first_token))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
