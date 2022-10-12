/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 06:19:36 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 20:53:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	t_list	**cur_el;
	char	**stock;
	char	*temp;

	cur_el = ft_retrieve_el(fd);
	stock = &(*cur_el)->stock;
	temp = ft_analyze_stock(cur_el, stock, fd);
	//free(*cur_el);
	return (temp);
}

t_list	**ft_retrieve_el(int fd)
{
	static t_list	*cur_el;
	t_list			*sch_el;

	sch_el = cur_el;
	while (sch_el && sch_el->fd != fd && sch_el->next != cur_el)
		sch_el = sch_el->next;
	if (!sch_el || sch_el->fd != fd)
	{
		cur_el = ft_edit_list(&sch_el, CREATE_ONE);
		cur_el->fd = fd;
		return (&cur_el);
	}
	cur_el = sch_el;
	return (&cur_el);
}

t_list	*ft_edit_list(t_list **ref_el, int action)
{
	t_list	*fcs_el;

	if (action == CREATE_ONE)
	{
		fcs_el = (t_list *)ft_mem_alloc(1, LIST_MALLOC);
		printf("create malloc : %p\n", fcs_el);
		fcs_el->stock = NULL;
		if (!*ref_el)
			*ref_el = fcs_el;
		else
			fcs_el->next = (*ref_el)->next;
		(*ref_el)->next = fcs_el;
		return (fcs_el);
	}
	fcs_el = *ref_el;
	while ((*ref_el)->next != fcs_el)
		*ref_el = (*ref_el)->next;
	if (fcs_el != *ref_el)
		(*ref_el)->next = fcs_el->next;
	else
		*ref_el = NULL;
	printf("free malloc stock : %p\n", fcs_el->stock);
	printf("free malloc : %p\n", fcs_el);
	free(fcs_el->stock);
	free(fcs_el);
	if (action == FREE_ALL && *ref_el)
		ft_edit_list(ref_el, FREE_ALL);
	return (NULL);
}

char	*ft_analyze_stock(t_list **cur_el, char **stock, int fd)
{
	int	index_nl;

	if (!*stock)
	{
		*stock = (char *)ft_mem_alloc(1, STR_MALLOC);
		if (!*stock)
			ft_edit_list(cur_el, FREE_ALL);
	}
	index_nl = ft_index_nl(*stock);
	if (index_nl == -1)
	{
		index_nl = ft_read_buffer(fd, stock);
		if (index_nl == -1)
		{
			*stock = NULL;
			ft_edit_list(cur_el, FREE_ONE);
			return (NULL);
		}
	}
	return (ft_update_stock(stock, ft_strjoin(stock, stock, LENGTH, 0),
			index_nl));
}

char	*ft_update_stock(char **stock, int stock_size, int index_nl)
{
	char	*new_line;

	new_line = ft_substr(stock, 0, index_nl + 1);
	*stock = ft_substr(stock, index_nl + 1, stock_size - index_nl - 1);
	return (new_line);
}
