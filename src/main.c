/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/10 21:43:51 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	t_token	*tokens;
	t_parse *parses;
	t_parse *first_parse;
	t_parse *temp;
	char *line;
	int		i;

	line = readline("> ");
	tokens = lex(line);
	free(line);
	parses = parse(tokens);
	first_parse = parses;
	while (parses->next != NULL)
	{
		i = 0;
		if (parses->cmd != NULL)
			printf("cmd :%s\n", parses->cmd);
		if (parses->args != NULL)
		{
			while (parses->args[i])
			{
				printf("args[%d] :%s\n", i, parses->args[i]);
				i++;
			}
		}
		if (parses->infile != NULL)
			printf("infile :%s\n", parses->infile);
		if (parses->outfile != NULL)
			printf("outfile :%s\n", parses->outfile);
		parses = parses->next;
	}
	parses = first_parse;
	while (parses->next != NULL)
	{
		temp = parses;
		i = 0;
		if (parses->cmd != NULL)
			free(parses->cmd);
		if (parses->args != NULL)
		{
			while (parses->args[i])
				free(parses->args[i++]);
			free(parses->args);
		}
		if (parses->infile != NULL)
			free(parses->infile);
		if (parses->outfile != NULL)
			free(parses->outfile);
		parses = parses->next;
		free(temp);
	}
	free(parses);
	return (0);
}
