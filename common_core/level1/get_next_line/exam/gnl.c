#define BUFFER_SIZE 42
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	static int i = 0;
	static int len = 0;
	int j = 0;
	char *line;
	char *tmp;
	int size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	line[0] = '\0';
	size = 0;
	while (1)
	{
		if (i >= len)
		{
			i = 0;
			len = read(fd, buf, BUFFER_SIZE);
			if (len <= 0)
			{
				if (size == 0)
				{
					free(line);
					return (NULL);
				}
				return (line);
			}
		}
		tmp = malloc(size + 2);
		if (!tmp)
			return (free(line), NULL);
		j = 0;
		while (j < size)
		{
			tmp[j] = line[j];
			j++;
		}
		tmp[size++] = buf[i++];
		tmp[size] = '\0';
		free(line);
		line = tmp;
		if (line[size - 1] == '\n')
			return (line);
	}
}

// int main (int ac, char **av)
// {
// 	(void)ac;
// 	int fd = open(av[1], O_RDONLY);
// 	char *line;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// }

