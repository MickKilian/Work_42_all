/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:44:12 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 04:45:18 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putnbr(unsigned int n);
int	ft_puthex(unsigned int n, int format);
int	ft_putptr(unsigned long long n);

#endif

