/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/17 22:03:22 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ms(t_ms *ms, char *envp[])
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	// init_token(ms->token); // 初期化しながら入力の処理をする
	// init_parse(ms->parse); // 同じく
	init_env(&(ms->env), envp);
}

int main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_token	*tokens;
	t_parse *parses;
	t_parse *first_parse;
	t_parse *temp;
	char *line;
	int		i;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		add_history(line);
		init_ms(&ms, envp);
		tokens = lex(line);
		free(line);
		t_token *temp2 = tokens;
		while (tokens->kinds != TK_EOF)
		{
			printf("word: %s\n", tokens->word);
			tokens = tokens->next;
		}
		tokens = temp2;
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
	}
	return (0);
}
