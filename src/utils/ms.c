/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:08:06 by motomo            #+#    #+#             */
/*   Updated: 2025/04/23 22:29:49 by kmoriyam         ###   ########.fr       */
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
		perror("ft_strdup");
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
		perror("ft_strjoin");
		exit(EXIT_FAILURE);
	}
	return (join);
}

char	*ms_strndup_pointer(char *start, char *end, t_ms *ms)
{
	char	*dup;

	dup = ft_strndup_pointer(start, end);
	if (!dup)
	{
		free_all(ms);
		perror("ft_strndup_pointer");
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
		perror("ft_substr");
		exit(EXIT_FAILURE);
	}
	return (result);
}
