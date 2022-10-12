/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:59:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2021/12/06 02:58:22 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size;

	i = 0;
	if (*(char *)little == '\0')
		return ((char *)big);
	size = ft_strlen(little);
	while ((ft_strlen((char *)(big + i)) >= size) && (i + size - 1 < len))
	{
		if (!ft_strncmp((char *)(big + i), little, size))
			return ((char *)big + i);
		else
			i++;
	}
	return (NULL);
}
