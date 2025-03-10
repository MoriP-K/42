/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/10 12:13:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	t_token	*tokens;
	t_parse *parses;
	
	tokens = lex(readline("> "));
	parses = parse(tokens);
	while (parses->next != NULL)
	{
		printf("cmd :%s\n", parses->cmd);
		parses = parses->next;
	}
	return (0);
}
