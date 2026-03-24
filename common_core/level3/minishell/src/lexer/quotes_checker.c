/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:19:59 by motomo            #+#    #+#             */
/*   Updated: 2025/05/01 19:36:45 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increment_switch_flag(int *count, int *flag)
{
	(*count)++;
	*flag = !(*flag);
}

void	count_quotes(t_token **token, int *doubleq, int *singleq)
{
	int	in_double_quote;
	int	in_single_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	while ((*token)->kinds != TK_EOF)
	{
		if ((*token)->kinds == TK_META
			&& (*token)->word[0] == '\"'
			&& !in_single_quote && !in_double_quote)
			increment_switch_flag(doubleq, &in_double_quote);
		else if ((*token)->kinds == TK_META
			&& (*token)->word[0] == '\"' && in_double_quote)
			increment_switch_flag(doubleq, &in_double_quote);
		else if ((*token)->kinds == TK_META
			&& (*token)->word[0] == '\''
			&& !in_double_quote && !in_single_quote)
			increment_switch_flag(singleq, &in_single_quote);
		else if ((*token)->kinds == TK_META
			&& (*token)->word[0] == '\'' && in_single_quote)
			increment_switch_flag(singleq, &in_single_quote);
		(*token) = (*token)->next;
	}
}

int	check_quote_count(t_token *token, t_ms *ms)
{
	int		double_quote_count;
	int		single_quote_count;
	t_token	*first_token;

	first_token = token;
	double_quote_count = 0;
	single_quote_count = 0;
	count_quotes(&token, &double_quote_count, &single_quote_count);
	if (double_quote_count % 2 == 1 || single_quote_count % 2 == 1)
	{
		print_syntax_error(token, ms);
		free_tokens(first_token);
		return (0);
	}
	return (1);
}
