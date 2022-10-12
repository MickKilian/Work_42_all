/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:50:15 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 04:44:53 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 10)
		count = ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}
