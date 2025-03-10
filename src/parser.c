/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:39:25 by root              #+#    #+#             */
/*   Updated: 2025/03/10 12:18:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *token)
{
	t_token *temp;

	while (token->kinds != TK_EOF)
	{
		temp = token;
		token = token->next;
		free(temp->word);
		free(temp);
	}
	free(token);
}

int count_args(t_token *token)
{
	int	count;

	count = 0;
	token = token->next;
	while (token->kinds != TK_META && token->kinds != TK_EOF)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_parse	*allocate_parse(t_token *token, t_parse *pre_parse)
{
	t_parse *new_parse;
	int		i;

	new_parse = (t_parse *)malloc(sizeof(t_parse));
	new_parse->cmd = NULL;
	new_parse->next = NULL;
	new_parse->infile = NULL;
	new_parse->outfile = NULL;
	if (!count_args(token))
		new_parse->args = NULL;
	else
	{
		new_parse->args = (char **)malloc((count_args(token) + 1) * sizeof(char *));
		new_parse->args[count_args(token)] = NULL;
	}
	i = 0;
	while (token->kinds != TK_EOF && !(token->kinds == TK_META && token->word[0] == '|'))
	{
		if (token->kinds != TK_META)
			new_parse->cmd = ft_strdup(token->word);
		else if (token->word[0] == '>')
		{
			new_parse->outfile = ft_strdup(token->next->word);
			token = token->next;
		}
		else if (token->word[0] == '<')
		{
			new_parse->infile = ft_strdup(token->next->word);
			token = token->next;
		}
		if (token->kinds != TK_EOF)
			token = token->next;
		while (new_parse->cmd != NULL && token->kinds != TK_META && token->kinds != TK_EOF)
		{
			new_parse->args[i++] = ft_strdup(token->word);
			token = token->next;
		}
	}
	if (pre_parse != NULL)
		pre_parse->next = new_parse;
	return(new_parse);
}

void add_EOF(t_parse *parse)
{
	t_parse	*EOF_parse;

	EOF_parse = (t_parse *)malloc(sizeof(t_parse));
	EOF_parse->cmd = NULL;
	EOF_parse->args = NULL;
	EOF_parse->infile = NULL;
	EOF_parse->outfile = NULL;
	EOF_parse->next = NULL;
	while (parse->next != NULL)
		parse = parse->next;
	parse->next = EOF_parse;
}

t_parse	*parse(t_token *token)
{
	t_token *first_token;
	t_parse	*first_parse;
	t_parse *current_parse;

	first_token = token;
	first_parse = allocate_parse(token, NULL);
	current_parse = first_parse;
	while (!(token->kinds == TK_META && token->word[0] == '|') && token->kinds != TK_EOF)
		token = token->next;
	if (token->kinds != TK_EOF)
		token = token->next;
	while (token->kinds != TK_EOF)
	{
		allocate_parse(token, current_parse);
		current_parse = current_parse->next;
		while ((token->kinds != TK_META && token->word[0] != '|') && token->kinds != TK_EOF)
			token = token->next;
		if (token->kinds != TK_EOF)
			token = token->next;
	}
	add_EOF(first_parse);
	free_tokens(first_token);
	return (first_parse);
}
