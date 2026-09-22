/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:39:27 by morip             #+#    #+#             */
/*   Updated: 2026/09/22 16:49:50 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

u_int16_t	checksum(void *data, size_t len)
{
	u_int32_t	sum;
	u_int16_t	*ptr;

	sum = 0;
	ptr = (u_int16_t *)data;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
		sum += *(u_int8_t *)ptr << 8;
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0xFFFF);
	return ((u_int16_t) ~ sum);
}
