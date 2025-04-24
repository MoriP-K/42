/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:38:13 by motomo            #+#    #+#             */
/*   Updated: 2025/04/24 21:14:12 by kmoriyam         ###   ########.fr       */
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

t_token	*init_token(t_ms *ms)
{
	t_token	*token;

	if (!ms)
		return (NULL);
	token = (t_token *)ms_malloc(sizeof(t_token), ms);
	token->kinds = TK_EOF;
	token->word = NULL;
	token->len = 0;
	token->single_quote = 0;
	token->quote = Q_NONE;
	token->next = NULL;
	return (token);
}

t_token	*copy_token_list(t_token *start, t_token *end, t_ms *ms)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*tmp;

	new_list = NULL;
	current = NULL;
	while (start && start != end)
	{
		tmp = init_token(ms);
		if (!tmp)
			return (NULL);
		tmp->kinds = start->kinds;
		if (start->word)
			tmp->word = ms_strdup(start->word, ms);
		if (!new_list)
			new_list = tmp;
		else
			current->next = tmp;
		current = tmp;
		start = start->next;
	}
	return (new_list);
}

t_parse	*allocate_parse(t_token *token, t_parse *pre_parse, t_ms *ms)
{
	t_parse	*new_parse;
	t_token	*start;
	int		i;

	new_parse = get_new_parse(ms, token);
	start = token;
	i = 1;
	while (token && token->kinds != TK_EOF && token->kinds != TK_PIPE)
	{
		if (token->kinds == TK_WORD)
			allocate_word(ms, &new_parse, &token, &i);
		else if ((token->kinds == TK_OUT_REDIRECT || token->kinds == TK_APPEND)
			&& token->next)
			allocate_append(ms, &new_parse, &token);
		else if ((token->kinds == TK_IN_REDIRECT || token->kinds == TK_HEREDOC)
			&& token->next)
			allocate_heredoc(ms, &new_parse, &token);
		token = token->next;
	}
	new_parse->token = copy_token_list(start, token, ms);
	if (pre_parse != NULL)
		pre_parse->next = new_parse;
	return (new_parse);
}
