/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/14 23:06:38 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"

# ifndef META_CHARS
#  define META_CHARS "\'\"<>| "
# endif

// initialize
void		init_ms(t_ms *ms, char *envp[]);
void		init_lexer(t_ms *ms, t_token **token, char *line);
void		init_parser(t_parse **parse, t_token *token);
void		init_env(t_env **env, char *envp[]);
void		init_exec(t_ms *ms, t_parse *parse, t_cl *cl);
void		init_fd(t_fd *fd, t_cl *cl);
void		init_proc(t_proc *proc, t_cl *cl);
void		init_cl(t_cl *cl, t_parse *parse);


t_token		*tokenizer(t_ms *ms, char *line);
int			check_quote_count(t_token *token);
int			syntax_error_handler(t_token *token);
//void		expand_token(t_token *token);
int			is_meta_char(char c);
char		**split_meta(char *line);
int			count_words(char *line);
t_token		*integrate_quotes(t_token *token);
t_token		*culling_space(t_token *token);
t_parse		*do_parse(t_token *token);
void		expand_token(t_ms *ms, t_token *token);

// signal
void		set_sigint_redisplay();
void		set_sigint_ign();

// utils
char		*ft_strndup(const char *start, const char *end);

// env
void		add_env_lst(t_env **node, t_env *new_env);
t_env		*last_env_lst(t_env *node);
t_env		*new_env_lst(void);
char		*get_env_value(char *env_var);
char		*get_env_key(char *env_var);

//envp
char 		**envp_dup(char **envp);
void		free_old_envp(char **envp);
int			find_env_index(char **envp, char *key);

// executer
void		set_pipe_fds(t_ms *ms, t_parse *parse, t_fd *fd, size_t index);
void		close_fds(t_ms *ms, t_fd *fd, size_t index);
void		close_all_fds(t_fd *fd, int cmd_count);
void		close_parent_fd(t_ms *ms, t_fd *fd, size_t index);
void		do_exec(t_ms *ms, t_parse *parse);
void		do_execve(t_ms *ms, t_parse *parse);
void		do_pipe(t_ms *ms, size_t index);
void		fail_to_fork(t_ms *ms);
void		find_cmd(t_ms *ms , t_parse *parse);
char		*find_cmd_path(char *cmd, t_env *env);
char		**add_slash(char **split_arr);
char		*join_cmd_and_path(char *cmd, char **split_arr);
char		*find_path_from_env(t_env *env);
int			is_executable_file(char *cmd);
int			check_builtin_cmd(char *cmd);
int			exec_built_in(t_ms *ms, t_parse *parse);


// free
void		free_ms(t_ms *ms);
void		free_tokens(t_token *token);
void		free_parser(t_parse *parse);
void		free_array(char **array);
void		free_fd(t_fd *fd, t_cl *cl);
void		free_env(t_env **env);
void		free_proc(t_proc *proc);

// builtins
int			builtin_pwd(void);
int			builtin_env(t_ms *ms);
int			builtin_export(t_ms *ms, t_parse *parse);
int			builtin_unset(t_ms *ms, t_parse *parse);
int			builtin_echo(t_parse *parse);
int			builtin_cd(t_ms *ms, t_parse *parse);
void		builtin_exit(t_ms *ms, t_parse *parse);

// error
void		throw_error(char *cmd);

#endif