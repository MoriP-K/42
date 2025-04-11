/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:32 by masa              #+#    #+#             */
/*   Updated: 2025/04/10 15:38:57 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd()
{
	char	*cwd;
	int		i;
	
	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		while (cwd[i])
			write(1, &cwd[i++], 1);
		free(cwd);
	}
	else
		perror("pwd");
}