/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:36:38 by motomo            #+#    #+#             */
/*   Updated: 2025/04/15 16:58:59 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_exit_status(t_ms *ms)
{
	return (ft_itoa(ms->exit_status));
}

char	*expand_join2(char **start, char **word, char **first, t_ms *ms)
{
	char	*env;
	char	*variable;

	if (**word != '$')
	{
		*start = *word;
		while (**word != '$')
			(*word)++;
		*first = ft_strndup(*start, *word);
	}
	(*word)++;
	*start = *word;
	while (**word != '$' && **word)
		(*word)++;
	variable = ft_strndup(*start, *word);
	env = get_value(ms->env, variable);
	free(variable);
	return (env);
}

void	expand_join3(char **first, char **env, char **result)
{
	if (*first != NULL)
	{
		*result = ft_strjoin(*first, *env);
		free((*first));
	}
	else
		*result = ft_strdup(*env);
	if (!(*env))
		*result = ft_strdup("");
}

char	*expand_join(t_ms *ms, char *word)
{
	char	*first_word;
	char	*env;
	char	*end_word;
	char	*start;
	char	*result;

	first_word = NULL;
	end_word = NULL;
	start = NULL;
	env = expand_join2(&start, &word, &first_word, ms);
	if (*word == '$')
	{
		start = word;
		while (*word)
			word++;
		end_word = ft_strndup(start, word);
	}
	expand_join3(&first_word, &env, &result);
	if (end_word != NULL)
	{
		result = ft_strjoin(result, end_word);
		free(end_word);
	}
	return (result);
}
