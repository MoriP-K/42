/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:42:52 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/15 22:50:36 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchr(char c);
int	ft_putaddress(unsigned long int address);
int	ft_puthex_lower(unsigned int num);
int	ft_puthex_upper(unsigned int num);
int	ft_putnbr_unsigned(unsigned int num);
int	ft_putnbr(int num);
int	ft_putstr(char *s);

#endif