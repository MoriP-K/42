/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:08:06 by motomo            #+#    #+#             */
/*   Updated: 2025/04/16 19:56:22 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ms_malloc(size_t size, t_ms *ms)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		free_all(ms);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char	*ms_strdup(char *str, t_ms *ms)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
	{
		free_all(ms);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (dup);
}

char	*ms_strjoin(char *s1, char *s2, t_ms *ms)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
	{
		free_all(ms);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (join);
}

char	*ms_strndup(char *start, char *end, t_ms *ms)
{
	char	*dup;

	dup = ft_strndup(start, end);
	if (!dup)
	{
		free_all(ms);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (dup);
}

char	*ms_substr(char *str, unsigned int start, size_t len, t_ms *ms)
{
	char	*result;

	result = ft_substr(str, start, len);
	if (!result)
	{
		free_all(ms);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}
