/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:36:38 by motomo            #+#    #+#             */
/*   Updated: 2025/04/16 19:08:03 by motomo           ###   ########.fr       */
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
		*first = ms_strndup(*start, *word, ms);
	}
	(*word)++;
	*start = *word;
	while (**word != '$' && **word)
		(*word)++;
	variable = ms_strndup(*start, *word, ms);
	env = get_value(ms->env, variable);
	free(variable);
	return (env);
}

void	set_env(char **first, char **env, char **result, t_ms *ms)
{
	if (*first != NULL)
	{
		if (*env)
			*result = ms_strjoin(*first, *env, ms);
		else
			*result = ms_strdup(*first, ms);
		free((*first));
	}
	else
	{
		if (*env)
			*result = ms_strdup(*env, ms);
		else
			*result = ms_strdup("", ms);
	}
}

void	set_end(char **result, char **end, t_ms *ms)
{
	char	*temp_for_free;

	if (*end != NULL)
	{
		temp_for_free = *result;
		*result = ms_strjoin(*result, *end, ms);
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
		end_word = ms_strndup(start, word, ms);
	}
	set_env(&first_word, &env, &result, ms);
	set_end(&result, &end_word, ms);
	return (result);
}
