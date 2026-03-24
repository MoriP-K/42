/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:43:17 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/24 15:27:15 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_return_str(char *line)
{
	if (!line)
		return (NULL);
	if (line[0])
		return (line);
	else
	{
		free(line);
		return (NULL);
	}
}

int	ft_getchar(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*buf_next;
	static int	n;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			buf_next = NULL;
			n = 0;
			return (-1);
		}
		buf_next = buf;
	}
	if (n > 0)
	{
		n--;
		return ((unsigned char)*buf_next++);
	}
	return (-1);
}

char	*ft_strjoin_char(char *line, char c)
{
	char	*combined_str;
	int		i;

	if (!line)
		return (NULL);
	combined_str = (char *)malloc(ft_strlen(line) + 1 + 1);
	if (!combined_str)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		combined_str[i] = line[i];
		i++;
	}
	combined_str[i] = c;
	combined_str[i + 1] = '\0';
	free(line);
	return (combined_str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
