/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:53:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:53:17 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
