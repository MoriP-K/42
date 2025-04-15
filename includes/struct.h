/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:46:02 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/14 22:59:05 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../src/libft/libft.h"

typedef struct s_ms t_ms;
typedef struct s_token t_token;
typedef struct s_parse t_parse;
typedef struct s_env t_env;
typedef struct s_fd t_fd;
typedef struct s_proc t_proc;
typedef struct s_cl t_cl;

typedef enum s_kinds
{
	TK_META = 1,
	TK_WORD = 2,
	TK_SPACE = 3,
	TK_IN_REDIRECT = 4,
	TK_OUT_REDIRECT = 5,
	TK_HEREDOC = 6,
	TK_APPEND = 7,
	TK_EOF = 8,
}	t_kinds;

typedef enum s_quote
{
	Q_NONE = 0,
	Q_SINGLE = 1,
	Q_DOUBLE = 2,
}	t_quote;

typedef enum s_timing {
	NONE = 0,
	INFILE = 1,
	OUTFILE = 2,
}			t_timing;

typedef struct s_token
{
	t_kinds			kinds;
	char			*word;
	size_t			len;
	int				single_quote;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*delimiter;
	int				append;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_fd
{
	int				infile;
	int				outfile;
	int				tmp_in;
	int				tmp_out;
	int				**pipe;
}	t_fd;

typedef struct s_proc
{
	pid_t			*id;
	int				status;
}			t_proc;

typedef struct s_cl
{
	size_t		cmd_count;
	char		*path;
}	t_cl;

typedef struct s_envp
{
	char			**envp;
}			t_envp;

typedef struct s_ms
{
	char			**envp;
	t_token			*token;
	t_parse			*parse;
	t_env			*env;
	int				exit_status;
	t_fd			fd;
	t_proc			proc;
	t_cl			cl;
}	t_ms;

#endif