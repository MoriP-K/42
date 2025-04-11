/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:43:40 by masa              #+#    #+#             */
/*   Updated: 2025/04/11 19:51:45 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**envp_dup(char **envp)
{
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (envp[count])
	{
		new_envp[count] = ft_strdup(envp[count]);
		count++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}