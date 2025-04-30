/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:23:12 by motomo            #+#    #+#             */
/*   Updated: 2025/04/30 23:14:36 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_kinds	get_kinds(char *word)
{
	t_kinds	kind;

	if (word[0] == EOF)
		kind = TK_EOF;
	else if (word[0] == ' ' || word[0] == '\t')
		kind = TK_SPACE;
	else if (word[0] == '<')
		kind = TK_IN_REDIRECT;
	else if (word[0] == '>')
		kind = TK_OUT_REDIRECT;
	else if (word[0] == '|')
		kind = TK_PIPE;
	else if (is_meta_char(word[0]))
		kind = TK_META;
	else
		kind = TK_WORD;
	return (kind);
}

void	lexer_add_eof(t_token *first_token, t_ms *ms)
{
	t_token	*token;
	t_token	*eof_token;

	eof_token = (t_token *)ms_malloc(sizeof(t_token), ms);
	eof_token->kinds = TK_EOF;
	eof_token->word = ms_strdup("", ms);
	eof_token->len = 0;
	eof_token->quote = Q_NONE;
	eof_token->next = NULL;
	token = first_token;
	while (token->next != NULL)
		token = token->next;
	token->next = eof_token;
}
