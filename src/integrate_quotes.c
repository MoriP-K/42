#include "../includes/minishell.h"

t_token *culling_space(t_token *token)
{
	t_token *first_token;
	t_token *temp;
	
	while (token->kinds == TK_SPACE && token->kinds != TK_EOF)
	{
		temp = token;
		token = token->next;
		free(temp->word);
		free(temp);
	}
	first_token = token;
	temp = token;
	while (token->kinds != TK_EOF)
	{
		if (token->kinds == TK_SPACE)
		{
			while (token->kinds == TK_SPACE && token->kinds != TK_EOF)
			{
				free(token->word);
				free(token);
				token = token->next;
			}
			temp->next = token;
		}
		temp = token;
		if (token->kinds != TK_EOF)
			token = token->next;
	}
	return (first_token);
}

t_token	*integrate_quotes(t_token *token)
{
	t_token *first_token;
	t_token *dest;
	t_token *temp;
	t_token *temp2;
	int		first_char_quote;
	int		i;

	first_char_quote = 0;
	if (token->kinds == TK_META && (token->word[0] == '\"' || token->word[0] == '\''))
		first_char_quote = 1;
	i = 0;
	first_token = token;
	while (token->kinds != TK_EOF)
	{
		if (token->next->kinds == TK_META && (token->next->word[0] == '\"' || token->next->word[0] == '\''))
			temp2 = token;
		if (token->kinds == TK_META && (token->word[0] == '\"' || token->word[0] == '\''))
		{
			if (token->word[0] == '\"')
				token->next->double_quote = 1;
			temp = token;
			token = token->next;
			free(temp->word);
			free(temp);
			dest = token;
			dest->kinds = TK_WORD;
			if (i++ == 0 && first_char_quote)
				first_token = dest;
			while (!((token->kinds == TK_META && (token->word[0] == '\"' || token->word[0] == '\'')) || token->kinds == TK_EOF))
			{
				temp = token;
				token = token->next;
					if ((token->kinds == TK_META && (token->word[0] == '\"' || token->word[0] == '\'')) || token->kinds == TK_EOF)
						break;
				dest->word = ft_strjoin(dest->word, token->word);
				if (temp != dest)
				{
					free(temp->word);
					free(temp);
				}
			}
			if (token->kinds == TK_EOF)
				return (NULL);
			else
			{
				temp = token;
				dest->next = token->next;
				free(temp->word);
				free(temp);
			}
			temp2->next = dest;
		}
		token = token->next;
	}
	return (first_token);
}
