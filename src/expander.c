/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:45 by motomo            #+#    #+#             */
/*   Updated: 2025/03/17 21:51:43 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_join(char *word)
{
	char	*first_word;
	char	*variable;
	char	*env;
	char	*end_word;
	char	*start;
	char	*result;

	first_word = NULL;
	end_word = NULL;
	if (*word != '$')
	{
		start = word;
		while (*word != '$')
			word++;
		first_word = ft_strndup(start, word);
	}
	word++;
	start = word;
	while(*word != '$' && *word)
		word++;
	variable = ft_strndup(start, word);
	env = getenv(variable);
	free(variable);
	if (*word == '$')
	{
		start = word;
		while(*word)
			word++;
		end_word = ft_strndup(start, word);
	}
	if (first_word != NULL)
	{
		result = ft_strjoin(first_word, env);
		free(first_word);
	}
	else
		result = ft_strdup(env);
	if (end_word != NULL)
	{
		result = ft_strjoin(result, end_word);
		free(end_word);
	}
	return (result);
}

t_token	*expand_env(t_token *token)
{
	int		i;
	int		has_dollor;
	char	*temp;

	i = 0;
	has_dollor = 0;
	temp = token->word;
	while (token->word[i])
	{
		if (token->word[i] == '$' && token->word[i + 1])
		{
			token->word = expand_join(token->word);
			i = 0;
			has_dollor = 1;
		}
		i++;
	}
	if (has_dollor == 1)
		free(temp);
	return (token);
}

void	expand_token(t_token *token)
{
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_WORD)
			token = expand_env(token);
		token = token->next;
	}
}