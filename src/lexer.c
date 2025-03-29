/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:39:55 by root              #+#    #+#             */
/*   Updated: 2025/03/26 20:33:05 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_kinds	get_kinds(char *word)
{
	t_kinds	kind;

	if(word[0] == EOF)
		kind = TK_EOF;
	else if (word[0] == ' ')
		kind = TK_SPACE;
	else if (is_meta_char(word[0]))
		kind = TK_META;
	else
		kind = TK_WORD;
	return (kind);
}

void	add_word_list(t_token *first_token, char *word)
{
	t_token	*token;
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->kinds = get_kinds(word);
	new_token->word = word;
	new_token->len = ft_strlen(word);
	new_token->double_quote = 0;
	new_token->next = NULL;
	token = first_token;
	while (token->next != NULL)
		token = token->next;
	token->next = new_token;
}

void	AddEOF(t_token *first_token)
{
	t_token	*token;
	t_token *EOF_token;

	EOF_token = (t_token *)malloc(sizeof(t_token));
	EOF_token->kinds = TK_EOF;
	EOF_token->word = "";
	EOF_token->len = 0;
	EOF_token->next = NULL;
	token = first_token;
	while (token->next != NULL)
		token = token->next;
	token->next = EOF_token;
}

t_token	*tokenizer(char *line)
{
    char	**words;
	t_token	*first_token;
	int		i;
	
	i = 1;
    words = split_meta(line);
	first_token = (t_token *)malloc(sizeof(t_token));
	first_token->next = NULL;
	first_token->kinds = get_kinds(words[0]);
	first_token->word = words[0];
	first_token->len = ft_strlen(words[0]);
	while (words[i])
		add_word_list(first_token, words[i++]);
	free(words);
	AddEOF(first_token);
	first_token = integrate_quotes(first_token);
	first_token = culling_space(first_token);
	return (first_token);
}
