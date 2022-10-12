/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:14:28 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 04:52:29 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list args, int c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'd')
		return (ft_putnbr(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), c));
	if (c == 'p')
		return (ft_putstr("0x") + ft_putptr(va_arg(args, unsigned long long)));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(char *str, ...)
{
	int	i;
	int	length_print;
	va_list	args;

	i = 0;
	length_print = 0;
	va_start(args, str);
	while (str[i])
	{
		while (str[i])
		{
			if (str[i] == '%')
			{
				length_print += ft_formats(args, str[i + 1]);
				i++;
			}
			else
				length_print += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (length_print);
}

int	main(void)
{
	char *str = "Bonjour monsieur";
	int	n = 5548;

	int	ft_res;
	int	res;

	ft_res = ft_printf("caractere : %c %%\n", str[0]);
	res = printf("caractere : %c %%\n", str[0]);
	printf("%d - %d\n", res, ft_res);
	ft_res = ft_printf("phrase : %s %% %% et caractrer 2 : %c\n", str, str[1]);
	res = printf("phrase : %s %% %% et caractrer 2 : %c\n", str, str[1]);
	printf("%d - %d\n", res, ft_res);
	res = ft_printf("nombre : %d\n", n);
	ft_res = printf("nombre : %d\n", n);
	printf("%d - %d\n", res, ft_res);
	res = ft_printf("nombre : %x\n", n);
	ft_res = printf("nombre : %x\n", n);
	printf("%d - %d\n", res, ft_res);
	res = ft_printf("nombre : %X\n", n);
	ft_res = printf("nombre : %X\n", n);
	printf("%d - %d\n", res, ft_res);
	res = ft_printf("adr : %p\n", &n);
	ft_res = printf("adr : %p\n", &n);
	printf("%d - %d\n", res, ft_res);
	return (0);
}
