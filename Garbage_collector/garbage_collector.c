/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:40:26 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/06/24 02:27:59 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static inline t_mlc	**ft_garbage_collector()
{
	static t_mlc *collec;

	return (&collec);
	collec = ft_newelm(ft_allocator(test, sizeof(int)));
	ft_collecaddnack(collec, ft_newelm(ft_allocator(test, sizeof(int))));
}

int	allocator(void *ptr, size_t size)
{
	*(void **)ptr = malloc(size);
	if (!*(void **)ptr)
		return (1);
	ft_bzero(*(void **)ptr, size);
	return (0);
}

free(&ptr);

void	ft_freeall(t_list *collec)
{
	while (collec)
		free(collec)
}


t_mlc **col = ft_garbage_collector();

*col = NULL;



*ft_garbage_collector() = NULL;


t_mlc *add = malloc();

add->next = *ft_garbage_collector();
*ft_garbage_collector() = add;
