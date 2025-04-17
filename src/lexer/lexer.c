/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:39:55 by root              #+#    #+#             */
/*   Updated: 2025/04/17 16:48:44 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_kinds	get_kinds(char *word)
{
	t_kinds	kind;

	if(word[0] == EOF)
		kind = TK_EOF;
	else if (word[0] == ' ' || word[0] == '\t')
		kind = TK_SPACE;
	else if (word[0] == '<') 
		kind = TK_IN_REDIRECT;
	else if (word[0] == '>')
		kind = TK_OUT_REDIRECT;
	else if (is_meta_char(word[0]))
		kind = TK_META;
	else
		kind = TK_WORD;
	return (kind);
}

void	add_word_list(t_token *first_token, char *word, t_ms *ms)
{
	t_token	*token;
	t_token *new_token;

	new_token = (t_token *)ms_malloc(sizeof(t_token), ms);
	new_token->kinds = get_kinds(word);
	new_token->word = word;
	new_token->len = ft_strlen(word);
	new_token->single_quote = 0;
	new_token->quote = Q_NONE;
	new_token->next = NULL;
	token = first_token;
	while (token->next)
		token = token->next;
	token->next = new_token;
}

void	AddEOF(t_token *first_token, t_ms *ms)
{
	t_token	*token;
	t_token *EOF_token;

	EOF_token = (t_token *)ms_malloc(sizeof(t_token), ms);
	EOF_token->kinds = TK_EOF;
	EOF_token->word = "";
	EOF_token->len = 0;
	EOF_token->quote = Q_NONE;
	EOF_token->next = NULL;
	token = first_token;
	while (token->next != NULL)
		token = token->next;
	token->next = EOF_token;
}

t_token	*combine_redirect(t_token *token, t_ms *ms)
{
	t_token	*first_token;
	char	*temp;
	t_token	*temp2;
	
	first_token = token;
	while (token->kinds != TK_EOF)
	{
		if ((token->kinds == TK_IN_REDIRECT && token->next->kinds == TK_IN_REDIRECT) 
			|| (token->kinds == TK_OUT_REDIRECT && token->next->kinds == TK_OUT_REDIRECT))
		{
			temp = token->word;
			temp2 = token->next;
			token->word = ms_strjoin(token->word, token->next->word, ms);
			if (token->kinds == TK_IN_REDIRECT)
				token->kinds = TK_HEREDOC;
			else if (token->kinds == TK_OUT_REDIRECT)
				token->kinds = TK_APPEND;
			free(temp);
			free(token->next->word);
			token->next = token->next->next;
			free(temp2);
		}
		token = token->next;
	}
	return (first_token);
}

t_token	*tokenizer(t_ms *ms, char *line)
{
    char	**words;
	t_token	*first_token;
	int		i;
	
	i = 1;
    words = split_meta(line, ms);
	first_token = (t_token *)ms_malloc(sizeof(t_token), ms);
	first_token->next = NULL;
	first_token->kinds = get_kinds(words[0]);
	first_token->word = words[0];
	first_token->len = ft_strlen(words[0]);
	first_token->single_quote = 0;
	while (words[i])
		add_word_list(first_token, words[i++], ms);
	free(words);
	AddEOF(first_token, ms);
	first_token = combine_redirect(first_token, ms);
	if (!check_quote_count(first_token))
		return(NULL);
	expand_token(ms, first_token);	
	first_token = integrate_quotes(first_token, ms);
	first_token = culling_space(first_token);
	if (!syntax_error_handler(first_token))
		return(NULL);
	return (first_token);
}
