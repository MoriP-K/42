/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:39:25 by root              #+#    #+#             */
/*   Updated: 2025/04/29 20:58:42 by kmoriyam         ###   ########.fr       */
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
	eof_parse->token = NULL;
	eof_parse->delimiter = NULL;
	eof_parse->heredoc_file = NULL;
	eof_parse->args = NULL;
	eof_parse->infile = NULL;
	eof_parse->outfile = NULL;
	eof_parse->next = NULL;
	eof_parse->append = 0;
	eof_parse->fd = NULL;
	while (parse->next != NULL)
		parse = parse->next;
	parse->next = eof_parse;
}

t_parse	*do_parse(t_token *token, t_ms *ms)
{
	t_token	*current_token;
	t_parse	*first_parse;
	t_parse	*current_parse;

	current_token = token;
	first_parse = allocate_parse(current_token, NULL, ms);
	current_parse = first_parse;
	while (current_token && current_token->kinds != TK_PIPE
		&& current_token->kinds != TK_EOF)
		current_token = current_token->next;
	if (current_token && current_token->kinds == TK_PIPE)
		current_token = current_token->next;
	while (current_token && current_token->kinds != TK_EOF)
	{
		current_parse = allocate_parse(current_token, current_parse, ms);
		while (current_token && current_token->kinds != TK_PIPE
			&& current_token->kinds != TK_EOF)
			current_token = current_token->next;
		if (current_token && current_token->kinds == TK_PIPE)
			current_token = current_token->next;
	}
	add_eof_parse(first_parse, ms);
	return (first_parse);
}
