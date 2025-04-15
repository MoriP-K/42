/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:36:38 by motomo            #+#    #+#             */
/*   Updated: 2025/04/15 20:39:27 by masa             ###   ########.fr       */
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

char	*set_start(char **start, char **word, char **first, t_ms *ms)
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

void	set_env(char **first, char **env, char **result)
{
	if (*first != NULL)
	{
		if (*env)
			*result = ft_strjoin(*first, *env);
		else
			*result = ft_strdup(*first);
		free((*first));
	}
	else
	{
		if (*env)
			*result = ft_strdup(*env);
		else
			*result = ft_strdup("");
	}
}

void	set_end(char **result, char **end)
{
	char	*temp_for_free;

	if (*end != NULL)
	{
		temp_for_free = *result;
		*result = ft_strjoin(*result, *end);
		free(temp_for_free);
		free(*end);
	}
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
	env = set_start(&start, &word, &first_word, ms);
	if (*word == '$')
	{
		start = word;
		while (*word)
			word++;
		end_word = ft_strndup(start, word);
	}
	set_env(&first_word, &env, &result);
	set_end(&result, &end_word);
	return (result);
}
