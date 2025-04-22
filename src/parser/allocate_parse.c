/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:38:13 by motomo            #+#    #+#             */
/*   Updated: 2025/04/22 20:20:46 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_word(t_ms *ms, t_parse **new_parse, t_token **token, int *i)
{
	if (!(*new_parse)->cmd)
	{
		(*new_parse)->cmd = ms_strdup((*token)->word, ms);
		(*new_parse)->args[0] = ms_strdup((*token)->word, ms);
	}
	else
		(*new_parse)->args[(*i)++] = ms_strdup((*token)->word, ms);
}

void	allocate_append(t_ms *ms, t_parse **new_parse, t_token **token)
{
	if ((*new_parse)->outfile)
		free((*new_parse)->outfile);
	(*new_parse)->outfile = ms_strdup((*token)->next->word, ms);
	if ((*token)->kinds == TK_APPEND)
		(*new_parse)->append = 1;
	(*token) = (*token)->next;
}

void	allocate_heredoc(t_ms *ms, t_parse **new_parse, t_token **token)
{
	if ((*new_parse)->infile)
		free((*new_parse)->infile);
	if ((*token)->kinds == TK_HEREDOC)
		(*new_parse)->delimiter = ms_strdup((*token)->next->word, ms);
	else
		(*new_parse)->infile = ms_strdup((*token)->next->word, ms);
	(*token) = (*token)->next;
}

t_parse	*allocate_parse(t_token *token, t_parse *pre_parse, t_ms *ms)
{
	t_parse	*new_parse;
	int		i;

	new_parse = get_new_parse(ms, token);
	new_parse->token = token;
	i = 1;
	while (token && token->kinds != TK_EOF && token->kinds != TK_PIPE)
	{
		if (token->kinds == TK_WORD)
			allocate_word(ms, &new_parse, &token, &i);
		else if ((token->kinds == TK_OUT_REDIRECT
				|| token->kinds == TK_APPEND) && token->next)
			allocate_append(ms, &new_parse, &token);
		else if ((token->kinds == TK_IN_REDIRECT
				|| token->kinds == TK_HEREDOC) && token->next)
			allocate_heredoc(ms, &new_parse, &token);
		if (token)
			token = token->next;
	}
	if (pre_parse != NULL)
		pre_parse->next = new_parse;
	return (new_parse);
}
