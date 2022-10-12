/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:57:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 19:22:25 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	if (ft_changestatus(philo, SLEEP))
		return (1);
	if (ft_myusleep(philo, philo->param->tm_sleep))
		return (1);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (ft_changestatus(philo, THINK))
		return (1);
	if (ft_myusleep(philo, THINK_MIN))
		return (1);
	return (0);
}

int	ft_changestatus(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->param->common_access_mutex);
	philo->status = status;
	if ((philo->param->death == -1
			&& philo->param->need_to_eat_count != 0)
		|| status == DIE)
	{
		printf("%ld %d %s\n", ft_gettime(philo->param->start) / 1000,
			philo->id, philo->param->txt_status[philo->status]);
		pthread_mutex_unlock(&philo->param->common_access_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->param->common_access_mutex);
		return (1);
	}
	return (0);
}
