/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:43:40 by masa              #+#    #+#             */
/*   Updated: 2025/04/16 19:00:37 by motomo           ###   ########.fr       */
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
