/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:13:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/30 13:56:10 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	throw_error(char *cmd)
{
	printf("Error: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	init_cl(t_cl *cl, t_parse *parse)
{
	t_parse *tmp;
	int		count;

	tmp = parse;
	count = 0;
	while (tmp)
	{
		if (tmp->cmd)
			count++;
		tmp = tmp->next;
	}
	printf("cmd count = %d\n", count);
	cl->cmd_count = count;
	cl->path = NULL;
}

void	init_proc(t_proc *proc, t_cl *cl)
{
	size_t	i;

	proc->id = malloc(sizeof(int) * cl->cmd_count);
	if (!proc->id)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < cl->cmd_count)
		proc->id[i++] = 0;
	proc->status = 0;
}

void	free_fd(t_fd *fd, t_cl *cl)
{
	size_t	i;

	i = 0;
	while (i < cl->cmd_count)
	{
		if (fd->pipe[i])
			free(fd->pipe[i]);
		i++;
	}
	free(fd->pipe);
}

void	init_fd(t_fd *fd, t_cl *cl)
{
	size_t	i;

	fd->pipe = malloc(sizeof(int *) * cl->cmd_count);
	if (!fd->pipe)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fd->infile = -1;
	fd->outfile = - 1;
	i = 0;
	while (i < cl->cmd_count)
	{
		fd->pipe[i] = malloc(sizeof(int) * 2);
		if (!fd->pipe[i])
		{
			perror("malloc");
			free_fd(fd, cl);
			exit(EXIT_FAILURE);
		}
		fd->pipe[i][0] = -1;
		fd->pipe[i][1] = -1;
		i++;
	}
}

void	init_exec(t_ms *ms, t_parse *parse, t_cl *cl)
{
	init_cl(&(ms->cl), parse);
	init_proc(&(ms->proc), cl);
	init_fd(&(ms->fd), cl);
}

void	init_lexer(t_token **token, char *line)
{
	*token = tokenizer(line);
	free(line);
}

void	init_parser(t_parse **parse, t_token *token)
{
	t_parse *first_parse;
	int		i;

	*parse = do_parse(token);
	first_parse = *parse;
	while (*parse)
	{
		i = 0;
		if ((*parse)->cmd != NULL)
			printf("cmd :%s\n", (*parse)->cmd);
		if ((*parse)->args != NULL)
		{
			while ((*parse)->args[i])
			{
				printf("args[%d] :%s\n", i, (*parse)->args[i]);
				i++;
			}
		}
		if ((*parse)->infile != NULL)
			printf("infile :%s\n", (*parse)->infile);
		if ((*parse)->outfile != NULL)
			printf("outfile :%s\n", (*parse)->outfile);
		*parse = (*parse)->next;
	}
	*parse = first_parse;
}

void	init_ms(t_ms *ms, char *envp[], char *line)
{
	ms->token = NULL;
	ms->parse = NULL;
	ms->env = NULL;
	ms->envp = envp;
	init_lexer(&(ms->token), line);
	init_parser(&(ms->parse), ms->token);
	init_env(&(ms->env), envp);
}

int	is_executable_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

char	*find_path_from_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, "PATH", 4) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_ms(t_ms *ms)
{
	(void)ms;
	return ;
}

void	free_parser(t_parse *parse)
{
	t_parse	*tmp;
	int		i;

	while (parse->next != NULL)
	{
		tmp = parse;
		i = 0;
		if (parse->cmd != NULL)
			free(parse->cmd);
		if (parse->args != NULL)
		{
			while (parse->args[i])
				free(parse->args[i++]);
			free(parse->args);
		}
		if (parse->infile != NULL)
			free(parse->infile);
		if (parse->outfile != NULL)
			free(parse->outfile);
		parse = parse->next;
		free(tmp);
	}
	free(parse);
}

char	*join_cmd_and_path(char *cmd, char **split_arr)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (split_arr[i])
	{
		path_cmd = ft_strjoin(split_arr[i], cmd);
		if (!path_cmd)
		{
			free_array(split_arr);
			return (NULL);
		}
		if (access(path_cmd, X_OK) == 0)
		{
			free_array(split_arr);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free_array(split_arr);
	return (NULL);
}

char	**add_slash(char **split_arr)
{
	int		i;
	char 	**added_slash_arr;
	int		arr_len;

	arr_len = ft_arrlen(split_arr);
	added_slash_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!added_slash_arr)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		added_slash_arr[i] = ft_strjoin(split_arr[i], "/");
		if (!added_slash_arr[i])
		{
			free_array(added_slash_arr);
			free_array(split_arr);
			return (NULL);
		}
		i++;
	}
	added_slash_arr[i] = NULL;
	free_array(split_arr);
	return (added_slash_arr);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*path;
	char	**split_arr;

	path = find_path_from_env(env);
	if (!path)
		return (NULL);
	split_arr = ft_split(path, ':');
	if (!split_arr)
		return (NULL);
	split_arr = add_slash(split_arr);
	if (!split_arr)
		return (NULL);
	return (join_cmd_and_path(cmd, split_arr));
}

void	find_cmd(t_ms *ms , t_parse *parse)
{
	if (ft_strchr(parse->cmd, '/'))
	{
		if (is_executable_file(parse->cmd))
			ms->cl.path = parse->cmd;
		else
		{
			free_ms(ms);
			throw_error(parse->cmd);
		}
	}
	else
	{
		ms->cl.path = find_cmd_path(parse->cmd, ms->env);
		if (!ms->cl.path)
		{
			free_ms(ms);
			throw_error(parse->cmd);
		}
	}
	write(1, "G\n", 2);

}

void	do_pipe(t_ms *ms, size_t index)
{
	if (index < ms->cl.cmd_count - 1)
	{
		if (pipe(ms->fd.pipe[index]) != 0)
		{
			// all_free();
			throw_error(ms->parse->cmd);
		}
	}
}

void	close_parent_fd(t_ms *ms, t_fd *fd, size_t index)
{
	if (!fd->pipe)
		return ;
	if (fd->infile > 0)
		close(fd->pipe[index][1]);
	else if (fd->outfile > 0)
		close(fd->pipe[index - 1][0]);
	else
	{
		if (index > 0 && index <= ms->cl.cmd_count && fd->pipe[index - 1])
		{
			close(fd->pipe[index - 1][0]);
		}
		if (index < ms->cl.cmd_count && fd->pipe[index])
			close(fd->pipe[index][1]);
	}
}

void	do_execve(t_ms *ms)
{
	execve(ms->cl.path, ms->parse->args, ms->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	close_all_fds(t_fd *fd, int cmd_count)
{
	int	i;

	if (fd->infile >= 0)
		close(fd->infile);
	if (fd->outfile >= 0)
		close(fd->outfile);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (fd->pipe[i][0] >= 0)
			close(fd->pipe[i][0]);
		if (fd->pipe[i][1] >= 0)
			close(fd->pipe[i][1]);
		i++;
	}
}

void	fail_to_fork(t_ms *ms)
{
	throw_error("fork");
	(void)ms;
	// all_free();
}

void	close_fds(t_ms *ms, t_fd *fd, size_t index)
{
	if (ms->cl.cmd_count > 1)
	{
		if (index == 0)
		{
			close(fd->pipe[index][0]);
		}
		if (index == ms->cl.cmd_count - 1)
		{
			close(fd->pipe[index - 1][1]);
		}
	}
}

void	set_pipe_fds(t_ms *ms, t_fd *fd, size_t index)
{
	// is_in_redirect();
	// is_out_redirect();
	if (ms->cl.cmd_count > 1)
	{
		if (index > 0 && fd->pipe[index - 1])
		{
			if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
			{
				throw_error("dup2_a");
				// all_free();
			}
		}
		if (index < ms->cl.cmd_count - 1 && fd->pipe[index])
		{
			if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
			{
				throw_error("dup2_b");
				// all_free();
			}
	}
	close_fds(ms, &(ms->fd), index);
}

void	do_exec(t_ms *ms, t_parse *parse)
{
	size_t	i;

	i = 0;
	while (i < ms->cl.cmd_count)
	{
		do_pipe(ms, i);
		ms->proc.id[i] = fork();
		if (ms->proc.id[i] == -1)
			fail_to_fork(ms);
		else if (ms->proc.id[i] == 0)
		{
			set_pipe_fds(ms, &(ms->fd), i);
			find_cmd(ms, parse);
			printf("cmd: %s\n", ms->cl.path);
			close_all_fds(&(ms->fd), ms->cl.cmd_count);
			do_execve(ms);
		}
		else
		{
			waitpid(ms->proc.id[i], &ms->proc.status, 0);
			close_parent_fd(ms, &(ms->fd), i);
		}
		parse = parse->next;
		i++;
	}
}

// void	test(t_ms *ms)
// {
// 	t_parse *parse;

// 	parse = malloc(sizeof(t_parse));
// 	ms->parse = parse;
// 	parse->cmd = ft_strdup("ls");
// 	parse->args = malloc(sizeof(char *) * 3);
// 	parse->args[0] = ft_strdup("ls");
// 	parse->args[1] = ft_strdup("-l");
// 	parse->args[2] = NULL;
// 	parse->infile = NULL;
// 	parse->outfile = NULL;
// 	parse->next = NULL;
// }

int main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char *line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("> ");
		init_ms(&ms, envp, line);
		init_exec(&ms, ms.parse, &(ms.cl));
		do_exec(&ms, ms.parse);
		free_parser(ms.parse);
		free_env(&ms.env);
	}
	return (0);
}
