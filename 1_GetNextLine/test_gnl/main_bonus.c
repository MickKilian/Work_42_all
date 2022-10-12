/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 01:26:58 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 20:44:12 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		i = -1;
	int		size_test;
	int		fd[6];
	char	file[][12] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt"};
	//int		test[] = {1, 2, 2, 4, 1, 4, 3, 3, 2, 1, 2, 2, 1, 5, 6};
	int		test[] = {1, 1, 1};
	char	*str = "";
	t_list	**cur_el;

	fd[4] = 42;
	fd[5] = 43;
	while (++i < 4)
	{
		fd[i] = open(file[i], O_RDONLY);
		if (fd[i] == -1)
			return (0);
	}
	i = -1;
	size_test = sizeof(test)/sizeof(test[0]);
	while (++i < size_test)
	{
		str = get_next_line(fd[test[i] - 1]);
		printf("next_line -> %s", str);
		if (str)
			free(str);
	}
	i = 0;
	while (++i < 4)
		close(fd[i]);
	cur_el = ft_retrieve_el(fd[1]);
	ft_edit_list(cur_el, FREE_ALL);
	return (0);
}
