/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:23:57 by root              #+#    #+#             */
/*   Updated: 2025/04/17 18:01:15 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_meta_char(char c)
{
	int	i;

	i = 0;
	while (META_CHARS[i])
	{
		if (c == META_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strndup(const char *start, const char *end)
{
	size_t	len;
	char	*dup;

	if (!start || !end || end < start)
		return (NULL);
	if (start == end)
	{
		dup = malloc(sizeof(char) * 2);
		dup = ft_memcpy(dup, start, 1);
		dup[1] = '\0';
		return (dup);
	}
	len = (size_t)(end - start);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	return (dup);
}

int	count_words(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!*line)
		return (0);
	while (line[i])
	{
		if (!is_meta_char(line[i]))
			count++;
		while (!is_meta_char(line[i]) && line[i])
			i++;
		if (is_meta_char(line[i]) && line[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**allocate_words(char *line, char **words, t_ms *ms)
{
	int		i;
	char	*start_char;

	i = 0;
	while (*line)
	{
		if (!is_meta_char(*line))
		{
			start_char = line;
			while (!is_meta_char(*(line)) && *(line))
				line++;
			words[i++] = ms_strndup(start_char, line, ms);
		}
		if (is_meta_char(*line))
		{
			words[i++] = ms_strndup(line, line, ms);
			line++;
		}
	}
	words[i] = NULL;
	return (words);
}

char	**split_meta(char *line, t_ms *ms)
{
	char	**words;

	words = (char **)ms_malloc((count_words(line) + 1) * sizeof(char *), ms);
	if (!words)
		return (NULL);
	words = allocate_words(line, words, ms);
	return (words);
}
