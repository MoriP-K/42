/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:39:25 by root              #+#    #+#             */
/*   Updated: 2025/04/05 20:26:58 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *token)
{
	t_token *temp;

	while (token && token->kinds != TK_EOF)
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
	while (token && token->kinds != TK_META && token->kinds != TK_EOF && token->kinds != TK_IN_REDIRECT && token->kinds != TK_OUT_REDIRECT)
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
	int		arg_count;

	arg_count = count_args(token);
	new_parse = (t_parse *)malloc(sizeof(t_parse));
	new_parse->cmd = NULL;
	new_parse->next = NULL;
	new_parse->infile = NULL;
	new_parse->outfile = NULL;
	new_parse->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	i = 0;
	while (i <= arg_count)
		new_parse->args[i++] = NULL;
	i = 1;
	while (token && token->kinds != TK_EOF && !(token->kinds == TK_META && token->word[0] == '|'))
	{
		if (token->kinds != TK_META && token->kinds != TK_IN_REDIRECT && token->kinds != TK_OUT_REDIRECT)
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
		while (new_parse->cmd != NULL && token->kinds == TK_WORD)
		{
			new_parse->args[i++] = ft_strdup(token->word);
			token = token->next;
		}
	}
	if (new_parse->cmd != NULL)
		new_parse->args[0] = ft_strdup(new_parse->cmd);
	else
	{
		free(new_parse->args);
		new_parse->args = NULL;
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

t_parse	*do_parse(t_token *token)
{
	t_token *first_token;
	t_parse	*first_parse;
	t_parse *current_parse;

	first_token = token;
	first_parse = allocate_parse(token, NULL);
	current_parse = first_parse;
	while (token && !(token->kinds == TK_META && token->word[0] == '|') && token->kinds != TK_EOF)
		token = token->next;
	if (token && token->kinds != TK_EOF)
		token = token->next;
	while (token && token->kinds != TK_EOF)
	{
		allocate_parse(token, current_parse);
		current_parse = current_parse->next;
		while (!(token->kinds == TK_META && token->word[0] == '|') && token->kinds != TK_EOF)
			token = token->next;
		if (token->kinds != TK_EOF)
			token = token->next;
	}
	add_EOF(first_parse);
	free_tokens(first_token);
	printf("infile: %s\n", current_parse->infile);
	return (first_parse);
}
