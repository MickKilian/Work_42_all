/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:50:15 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 04:50:31 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long n)
{
	int	count;

	count = 0;
	if (n > 16)
		count = ft_putptr(n / 16);
	n = n % 16;
	if (n < 10)
		count += ft_putchar(n + '0');
	else
		count += ft_putchar(n - 10 + 'a');
	return (count);
}
