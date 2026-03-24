/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:43:40 by masa              #+#    #+#             */
/*   Updated: 2025/04/17 21:14:03 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**envp_dup(char **envp, t_ms *ms)
{
	int		count;
	char	**new_envp;

	count = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[count])
		count++;
	new_envp = (char **)ms_malloc(sizeof(char *) * (count + 1), ms);
	count = 0;
	while (envp[count])
	{
		new_envp[count] = ms_strdup(envp[count], ms);
		count++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

int	find_env_index(char **envp, char *key)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	export_has_wrong_char(char *arg)
{
	if (!(ft_isalpha(arg[0]) || ft_memcmp(arg, "_", 1) == 0))
		return (1);
	while (*arg && *arg != '=')
	{
		if (!(ft_isalnum((int)*arg) || ft_memcmp(arg, "_", 1) == 0))
			return (1);
		arg++;
	}
	return (0);
}

void	free_old_envp(char **envp)
{
	int	i;
	int	count;

	i = 0;
	if (!envp)
		return ;
	count = 0;
	while (envp[i++])
		count++;
	i = 0;
	while (envp[i] && i < count)
		free(envp[i++]);
	free(envp);
}

int	export_error(char *arg)
{
	write(2, "export: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}
