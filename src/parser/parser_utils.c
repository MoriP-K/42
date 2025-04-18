/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:01:55 by motomo            #+#    #+#             */
/*   Updated: 2025/04/17 21:02:29 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->kinds != TK_META
		&& token->kinds != TK_EOF
		&& token->kinds != TK_IN_REDIRECT
		&& token->kinds != TK_OUT_REDIRECT)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_parse	*get_new_parse(t_ms *ms, t_token *token)
{
	t_parse	*new_parse;
	int		arg_count;
	int		i;

	arg_count = count_args(token);
	new_parse = (t_parse *)ms_malloc(sizeof(t_parse), ms);
	new_parse->cmd = NULL;
	new_parse->next = NULL;
	new_parse->infile = NULL;
	new_parse->outfile = NULL;
	new_parse->append = 0;
	new_parse->args = (char **)ms_malloc(sizeof(char *) * (arg_count + 1), ms);
	i = 0;
	while (i <= arg_count)
		new_parse->args[i++] = NULL;
	return (new_parse);
}
