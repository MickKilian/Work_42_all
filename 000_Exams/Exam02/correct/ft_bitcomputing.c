/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitcomputing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:51:48 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 15:06:28 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

unsigned char	ft_bitcomputing(unsigned char c)
{
	return (~c);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		printf("reverse : %d\n", ft_bitcomputing(atoi(argv[1])));
	return (0);
}
