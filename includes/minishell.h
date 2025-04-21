/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/21 22:01:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struct.h"

# ifndef META_CHARS
#  define META_CHARS "\'\" <>"
# endif

// initialize
void		init_ms(t_ms *ms, char *envp[]);
void		init_lexer(t_ms *ms, t_token **token, char *line);
void		init_parser(t_parse **parse, t_token *token, t_ms *ms);
void		init_env(t_env **env, char *envp[], t_ms *ms);
void		init_exec(t_ms *ms, t_parse *parse);
void		init_fd(t_fd **fd, t_cl *cl, t_ms *ms);
void		init_proc(t_proc **proc, t_cl *cl, t_ms *ms);
void		init_cl(t_cl **cl, t_parse *parse, t_ms *ms);

//lexer
t_token		*tokenizer(t_ms *ms, char *line);
t_kinds		get_kinds(char *word);
void		lexer_add_eof(t_token *first_token, t_ms *ms);
int			check_quote_count(t_token *token);
int			syntax_error_handler(t_token *token);
int			is_meta_char(char c);
char		**split_meta(char *line, t_ms *ms);
int			count_words(char *line);
t_token		*integrate_quotes(t_token *token, t_ms *ms);
t_token		*combine_all(t_token *token, t_ms *ms);
t_token		*get_empty_token(t_token *next, t_ms *ms);
t_token		*culling_space(t_token *token);

//parser
t_parse		*do_parse(t_token *token, t_ms *ms);
t_parse		*allocate_parse(t_token *token, t_parse *pre_parse, t_ms *ms);
t_parse		*get_new_parse(t_ms *ms, t_token *token);

// expander
void		expand_token(t_ms *ms, t_token *token);
char		*get_exit_status(t_ms *ms);
char		*expand_join(t_ms *ms, char *word);

// signal
void		set_sigint_redisplay(void);
void		set_sigint_ign(void);

// utils

char		*ft_strndup_pointer(const char *start, const char *end);

// malloc
void		*ms_malloc(size_t size, t_ms *ms);
char		*ms_strdup(char *str, t_ms *ms);
char		*ms_strjoin(char *s1, char *s2, t_ms *ms);
char		*ms_strndup_pointer(char *start, char *end, t_ms *ms);
char		*ms_substr(char *str, unsigned int start, size_t len, t_ms *ms);

// env
void		add_env_lst(t_env **node, t_env *new_env);
t_env		*last_env_lst(t_env *node);
t_env		*new_env_lst(t_ms *ms);
char		*get_env_value(char *env_var, t_ms *ms);
char		*get_env_key(char *env_var, t_ms *ms);
char		*get_value(t_env *env, char *key);

//envp
char		**envp_dup(char **envp, t_ms *ms);
void		free_old_envp(char **envp);
int			find_env_index(char **envp, char *key);

// executer
void		set_pipe_fds(t_ms *ms, t_parse *parse, t_fd *fd, size_t index);
void		close_fds(t_ms *ms, t_fd *fd, size_t index);
void		close_all_fds(t_fd *fd, int cmd_count);
void		close_parent_fd(t_ms *ms, t_fd *fd, size_t index);
int			do_exec(t_ms *ms, t_parse *parse);
void		do_execve(t_ms *ms, t_parse *parse);
void		do_pipe(t_ms *ms, size_t index);
void		fail_to_fork(t_ms *ms);
void		find_cmd(t_ms *ms, t_parse *parse);
char		*find_cmd_path(char *cmd, t_env *env, t_ms *ms);
char		**add_slash(char **split_arr, t_ms *ms);
char		*join_cmd_and_path(char *cmd, char **split_arr, t_ms *ms);
char		*find_path_from_env(t_env *env);
int			is_executable_file(char *cmd);
int			check_builtin_cmd(char *cmd);
int			exec_built_in(t_ms *ms, t_parse *parse);

// free
void		free_all(t_ms *ms);
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
void		env_pwd_changer(t_ms *ms);
void		builtin_exit(t_ms *ms, t_parse *parse);
void		export_sort(t_ms *ms);
int			find_env_index(char **envp, char *key);
int			export_error(char *arg);
int			export_has_wrong_char(char *arg);

// error
void		throw_error(char *cmd);

#endif