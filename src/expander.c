/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:52:45 by motomo            #+#    #+#             */
/*   Updated: 2025/04/12 19:59:26 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_join(t_ms *ms, char *word)
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
	env = get_value(ms->env, variable);
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
	if (!env)
		result = ft_strdup("");
	if (end_word != NULL)
	{
		result = ft_strjoin(result, end_word);
		free(end_word);
	}
	return (result);
}

t_token	*expand_env(t_ms *ms, t_token *token)
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
			token->word = expand_join(ms, token->word);
			i = -1;
			has_dollor = 1;
		}
		i++;
	}
	if (has_dollor == 1)
		free(temp);
	return (token);
}

void	expand_token(t_ms *ms, t_token *token)
{
	size_t	in_single_quote;
	size_t	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_META && token->word[0] == '\'')
		{
			if (!in_double_quote)
				in_single_quote = !in_single_quote;
			else
				token->kinds = TK_WORD;
		}
		else if (token->kinds == TK_META && token->word[0] == '\"')
		{	
			if (!in_single_quote)
				in_double_quote = !in_double_quote;
			else
				token->kinds = TK_WORD;
		}
		if (token->kinds == TK_WORD && token->single_quote != 1 && (!in_single_quote || in_double_quote))
			token = expand_env(ms, token);
		token = token->next;
	}

}
