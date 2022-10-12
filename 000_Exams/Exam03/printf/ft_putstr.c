/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:28:00 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 03:46:08 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count += ft_putchar (str[i]);
		i++;
	}
	return (count);
}
