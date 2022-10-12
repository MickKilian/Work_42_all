/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:49:28 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 09:50:17 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("input.txt", O_RDONLY);
	//printf("here\n");
	str = ft_getnextline(fd);
	while (*str)
	{
		printf("%s", str);
		free(str);
		str = ft_getnextline(fd);
	}
	free(str);
	return (0);
}
