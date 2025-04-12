/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:34:43 by masa              #+#    #+#             */
/*   Updated: 2025/04/12 12:37:41 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_error(char *path)
{
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 29);
}

char	*find_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	builtin_cd(t_ms *ms, t_parse *parse)
{
	char	*env_value;

	if (parse->args == NULL || parse->args[1] == NULL)
	{
		env_value = find_value(ms->env, "HOME");
		if (!env_value)
		{
			write(2, "cd: HOME not set\n", 17);
			return;
		}
		else if (chdir(env_value) != 0)
			write_cd_error(env_value);
		return;
	}
	if (parse->args[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		return;
	}
	if (chdir(parse->args[1]) != 0)
		write_cd_error(parse->args[1]);				
}
