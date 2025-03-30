/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/30 16:49:30 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"

# ifndef META_CHARS
#  define META_CHARS "\'\"<>| "
# endif

// minishell
void		init_ms(t_ms *ms, char *envp[], char *line);

t_token		*tokenizer(char *line);
int			check_quote_count(t_token *token);
int			syntax_error_handler(t_token *token);
void		expand_token(t_token *token);
int			is_meta_char(char c);
char		**split_meta(char *line);
int			count_words(char *line);
t_token		*integrate_quotes(t_token *token);
t_token		*culling_space(t_token *token);
t_parse		*do_parse(t_token *token);

// utils

char		*ft_strndup(const char *start, const char *end);

// env
void		init_env(t_env **env, char *envp[]);
void		add_env_lst(t_env **node, t_env *new_env);
t_env		*last_env_lst(t_env *node);
t_env		*new_env_lst(void);
char		*get_env_value(char *env_var);
char		*get_env_key(char *env_var);
void		free_env(t_env **env);

#endif