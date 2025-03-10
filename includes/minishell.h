/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/10 12:05:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"

# ifndef META_CHARS
# define META_CHARS "\'\"$<>| "
# endif

t_token	*lex(char *line);
int	is_meta_char(char c);
char **split_meta(char *line);
int count_words(char *line);
t_token	*integrate_quotes(t_token *token);
t_token *culling_space(t_token *token);
t_parse	*parse(t_token *token);

#endif