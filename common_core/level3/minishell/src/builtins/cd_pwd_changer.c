/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_changer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:18:42 by motomo            #+#    #+#             */
/*   Updated: 2025/04/17 21:34:32 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd_value(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	oldpwd_unset(t_ms *ms)
{
	t_parse	*parse;
	char	**args;

	parse = (t_parse *)ms_malloc(sizeof(t_parse) * 1, ms);
	args = (char **)ms_malloc(sizeof(char *) * 3, ms);
	args[2] = NULL;
	args[1] = ms_strdup("OLDPWD", ms);
	parse->args = args;
	builtin_unset(ms, parse);
	free(args[1]);
	free(args);
	free(parse);
}

void	oldpwd_new_export(t_ms *ms, char *pwd)
{
	t_parse	*parse;
	char	**args;
	char	*key;
	char	*value;

	parse = (t_parse *)ms_malloc(sizeof(t_parse) * 1, ms);
	args = (char **)ms_malloc(sizeof(char *) * 3, ms);
	args[2] = NULL;
	key = ms_strdup("OLDPWD=", ms);
	value = ms_strdup(pwd, ms);
	args[1] = ms_strjoin(key, value, ms);
	free(key);
	free(value);
	parse->args = args;
	parse->next = NULL;
	builtin_export(ms, parse);
	free(args[1]);
	free(args);
	free(parse);
}

int	env_oldpwd_changer(t_ms *ms)
{
	char	*pwd;

	pwd = get_pwd_value(ms);
	if (pwd == NULL)
		oldpwd_unset(ms);
	else
		oldpwd_new_export(ms, pwd);
	if (pwd == NULL)
		return (0);
	return (1);
}

void	env_pwd_changer(t_ms *ms)
{
	t_parse	*parse;
	char	**args;
	char	*key;
	char	*value;
	char	*cwd;

	if (!env_oldpwd_changer(ms))
		return ;
	parse = (t_parse *)ms_malloc(sizeof(t_parse) * 1, ms);
	args = (char **)ms_malloc(sizeof(char *) * 3, ms);
	key = ms_strdup("PWD=", ms);
	cwd = getcwd(NULL, 0);
	value = ms_strdup(cwd, ms);
	free(cwd);
	args[1] = ms_strjoin(key, value, ms);
	free(key);
	free(value);
	args[2] = NULL;
	parse->args = args;
	parse->next = NULL;
	builtin_export(ms, parse);
	free(args[1]);
	free(args);
	free(parse);
}
