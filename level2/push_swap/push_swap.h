/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:10:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 14:17:12 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

void			sa(int *a);
void			sb(int *b);
void			ss(int *a, int *b);
void			pa(t_stack *a, t_stack *b);
void			pb(t_stack *a, t_stack *b);
void			ra(t_stack *a);
void			rb(t_stack *b);
void			rr(t_stack *a, t_stack *b);
void			rra(t_stack *a);
void			rrb(t_stack *b);
void			rrr(t_stack *a, t_stack *b);
void			sort(int *compressed, t_stack *a);
int				is_sorted(t_stack *a);
int				check_double(t_stack *a);
int				ft_memflow(int sign, long result, char **endptr, char *nptr);
int				set_endptr(long result, char **endptr, char *nptr);
long			ft_strtol(const char *nptr, char **endptr);
char			**set_arg(int ac, char **av, t_stack *a, int *is_alloated);
void			free_array(char **array);
int				ft_int(long long num, char **array, char *endptr, int is_allocated);
int				validate_arg(int ac, char **av, t_stack *a);
int				*numcpy(int *dest, t_stack *a);
int				assign_index(int *copmressed, int num, int len);
void			compress_stack(t_stack *a);
void			check_cmds(t_list *cmd_lists);
void			write_cmd(t_command cmd);
void			print_cmds(t_list *cmd_lists);
void			exec_swap(t_stack *a, t_stack *b, t_command cmd);
void			exec_rotate(t_stack *a, t_stack *b, t_command cmd);
void			exec_reverse_rotate(t_stack *a, t_stack *b, t_command cmd);
void			exec_push(t_stack *a, t_stack *b, t_command cmd);
void			add_cmd(t_list **cmd_lists, t_command cmd);
void			exec_cmd(t_command cmd, t_stack *a, t_stack *b, t_list **cmd_lists);
int				search_max_index(t_stack *stack);
int				search_min_index(t_stack *stack);
void			search_min_pb(t_stack *a, t_stack *b, t_list **cmd_lists);
void			search_max_pa(t_stack *a, t_stack *b, t_list **cmd_lists);
void			sort_two(t_stack *a, t_stack *b, t_list **cmd_lists);
void			sort_three(t_stack *a, t_stack *b, t_list **cmd_lists);
void			sort_four(t_stack *a, t_stack *b, t_list **cmd_lists);
void			sort_more_than_five(t_stack *a, t_stack *b, t_list **cmd_lists);
int				is_in_range(int num, int min, int max);
int				split_chunk_size(int len);
void			exec_pb_rb(t_stack *a, t_stack *b, t_list **cmd_lists);
void			sort_by_chunky(t_stack *a, t_stack *b, t_list **cmd_lists);
void			free_structure(t_stack **a, t_stack **b, t_list **cmd_lists);
int				init_structure(t_stack **a, t_stack **b, t_list **cmd_lists);
void			start_sort(t_stack *a, t_stack *b, t_list **cmd_lists);

#endif