/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:10:24 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 14:17:49 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum s_command {
	NONE = 0,
	SA = 1,
	SB = 2,
	SS = 3,
	RA = 4,
	RB = 5,
	RR = 6,
	RRA = 7,
	RRB = 8,
	RRR = 9,
	PA = 10,
	PB = 11,
}	t_command;

typedef struct s_stack
{
	int	data[50000];
	int	len;
}	t_stack;

#endif