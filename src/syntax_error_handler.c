/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:27:27 by motomo            #+#    #+#             */
/*   Updated: 2025/03/30 14:27:29 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(t_token *token)
{
	write(1, "minishell: syntax error near unexpected token `", 47);
	write(1, token->word, ft_strlen(token->word));
	write(1, "\'\n", 2);
}

// int	pipe_error(t_token *token)
// {
	
// }

// int	redirect_error(t_token *token)
// {
	
// }

int	syntax_error_handler(t_token *token)
{
	int	double_quote_count;
	int	single_quote_count;
	
	double_quote_count = 0;
	single_quote_count = 0;
	while (token->kinds != TK_EOF)
	{
		print_error(token);
		token = token->next;
	}
	return (1);
}