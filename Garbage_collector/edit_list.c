/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:50:56 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/06/24 02:02:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_list	*ft_newelm(void *mlc)
{
	t_list	*newelm;

	if (allocator(&newelm, sizeof(t_list)))
		return (NULL);
	newelm->address = mlc;
	newelm->prev = newelm;
	newelm->next = newelm;
	return (newelm);
}

int	ft_collecaddback(t_list *collec, t_list *new)
{
	if (!new)
		return (1);
	new->prev = collec->prev;
	new->next = collec;
	if (collec->next == stack)
		collec->next = new;
	else
		collec->prev->next = new;
	collec->prev = new;
	return (0);
}
