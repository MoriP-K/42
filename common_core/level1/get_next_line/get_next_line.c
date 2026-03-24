/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:00:59 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/24 15:18:07 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*line_ptr;
	int		c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		c = ft_getchar(fd);
		if (c == -1)
			return (ft_return_str(line));
		line_ptr = ft_strjoin_char(line, (char)c);
		if (!line_ptr)
			return (NULL);
		line = line_ptr;
		if (c == '\n')
			break ;
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*s;

// 	fd = open("memo.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (1)
// 	{
// 		s = get_next_line(fd);
// 		if (!s)
// 		{
// 			break ;
// 		}
// 		printf("%s", s);
// 		free(s);
// 	}
// 	close(fd);
// }
