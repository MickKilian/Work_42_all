/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:42:16 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/06/24 02:08:51 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_mlc
{

	int		address;
	t_list	*next;
}	t_mlc;

#endif
