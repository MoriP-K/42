/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:46:02 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/16 16:58:37 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/libft.h"

typedef enum s_kinds
{
	TK_META = 1,
	TK_WORD = 2,
	TK_SPACE = 3,
	TK_EOF = 4,
}	t_kinds;

typedef struct s_token
{
	t_kinds			kinds;
	char			*word;
	size_t			len;
	int				double_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	t_token	*token;
	t_parse	*parse;
	t_env	*env;
}	t_ms;

#endif