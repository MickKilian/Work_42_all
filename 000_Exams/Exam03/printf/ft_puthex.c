/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:50:15 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 04:42:57 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, int format)
{
	int	count;

	count = 0;
	if (n > 16)
		count = ft_puthex(n / 16, format);
	if ((n % 16) < 10)
		count += ft_putchar((n % 16) + '0');
	else
	{
		if (format == 'X')
			count += ft_putchar((n % 16) - 10 + 'A');
		else if (format == 'x')
			count += ft_putchar((n % 16) - 10 + 'a');
	}
	return (count);
}
