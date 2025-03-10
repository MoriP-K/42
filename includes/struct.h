/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:46:02 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/10 12:12:51 by root             ###   ########.fr       */
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

typedef enum
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
	char 			*outfile;
	struct	s_parse	*next;
}	t_parse;

#endif