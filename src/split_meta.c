/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:23:57 by root              #+#    #+#             */
/*   Updated: 2025/03/10 12:14:56 by root             ###   ########.fr       */
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
	char	*dest;
	size_t	len;
	size_t	index;

	if (start == end)
	{
		dest = malloc(2);
		dest[0] = *start;
		dest[1] = '\0';
		return (dest);
	}
	len = end - start;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	index = 0;
	while (start < end)
	{
		dest[index] = *start;
		index++;
		start++;
	}
	dest[index] = '\0';
	return (dest);
}

int count_words(char *line)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	if (!*line)
		return (0);
	while (line[i])
	{
		if (!is_meta_char(line[i]))
			count++;
		while(!is_meta_char(line[i]) && line[i])
			i++;
		if (is_meta_char(line[i]) && line[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**allocate_words(char *line, char **words)
{
	int	i;
	char *start_char;

	i = 0;
	while (*line)
	{
		if (!is_meta_char(*line))
		{
			start_char = line;
			while (!is_meta_char(*(line)) && *(line))
				line++;
			words[i++] = ft_strndup(start_char, line);
		}
		if (is_meta_char(*line))
		{
			words[i++] = ft_strndup(line, line);
			line++;
		}
	}
	words[i] = NULL;
	return (words);
}

char **split_meta(char *line)
{
	char    **words;

	words = (char **)malloc((count_words(line) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	words = allocate_words(line, words);
	return (words);
}
