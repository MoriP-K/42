/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:39:25 by root              #+#    #+#             */
/*   Updated: 2025/04/17 21:04:17 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token && token->kinds != TK_EOF)
	{
		temp = token;
		token = token->next;
		free(temp->word);
		free(temp);
	}
	free(token);
}

void	add_eof_parse(t_parse *parse, t_ms *ms)
{
	t_parse	*eof_parse;

	eof_parse = (t_parse *)ms_malloc(sizeof(t_parse), ms);
	eof_parse->cmd = NULL;
	eof_parse->args = NULL;
	eof_parse->infile = NULL;
	eof_parse->outfile = NULL;
	eof_parse->next = NULL;
	while (parse->next != NULL)
		parse = parse->next;
	parse->next = eof_parse;
}

t_parse	*do_parse(t_token *token, t_ms *ms)
{
	t_token	*first_token;
	t_parse	*first_parse;
	t_parse	*current_parse;

	first_token = token;
	first_parse = allocate_parse(token, NULL, ms);
	current_parse = first_parse;
	while (token && !(token->kinds == TK_META && token->word[0] == '|')
		&& token->kinds != TK_EOF)
		token = token->next;
	if (token && token->kinds != TK_EOF)
		token = token->next;
	while (token && token->kinds != TK_EOF)
	{
		allocate_parse(token, current_parse, ms);
		current_parse = current_parse->next;
		while (!(token->kinds == TK_META && token->word[0] == '|')
			&& token->kinds != TK_EOF)
			token = token->next;
		if (token->kinds != TK_EOF)
			token = token->next;
	}
	add_eof_parse(first_parse, ms);
	free_tokens(first_token);
	return (first_parse);
}
