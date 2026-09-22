/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:50:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/09/22 16:54:37 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	set_icmp_header(t_tr *tr)
{
	tr->icmp.type = 8;
	tr->icmp.code = 0;
	tr->icmp.id = getpid() & 0xFFFF;
	tr->icmp.sequence = 1;
	memset(tr->icmp.data, 0, sizeof(tr->icmp.data));
	tr->icmp.checksum = checksum((uint16_t *)&tr->icmp, sizeof(tr->icmp));
}
