/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:50:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/09/22 16:03:40 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	set_icmp(t_tr *tr)
{
	uint16_t		checksum;

	tr->icmp.type = 8;
	tr->icmp.code = 0;
	tr->icmp.id = 
	tr->icmp.sequence = 1;
}
