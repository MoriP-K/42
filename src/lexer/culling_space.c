/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culling_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:10:56 by masa              #+#    #+#             */
/*   Updated: 2025/04/15 21:19:01 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	culling_first_space(t_token **token)
{
	t_token *temp;

	while ((*token)->kinds == TK_SPACE && (*token)->kinds != TK_EOF)
	{
		temp = *token;
		*token = (*token)->next;
		free(temp->word);
		free(temp);
	}
}

t_token	*culling_space(t_token *token)
{
	t_token *first_token;
	t_token *temp;
	t_token	*temp2;
	
	culling_first_space(&token);
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
