/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:06:46 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/07 00:31:42 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_monitoring(t_philo *philo)
{
	while (1)
	{
		if (ft_checkenougheat(philo) || ft_checkdeath(philo))
			return (1);
		ft_myusleep(philo, USLEEP_INC);
	}
	return (0);
}

int	ft_checkdeath(t_philo *philo)
{
	int		i;

	i = 0;
	while (++i <= philo->param->nb_philos)
	{
		pthread_mutex_lock(&philo->param->common_access_mutex);
		if (philo->status != EAT && ft_gettime(philo->param->start)
			>= philo->last_eat + philo->param->tm_die)
		{
			philo->param->death = philo->id;
			pthread_mutex_unlock(&philo->param->common_access_mutex);
			ft_changestatus(philo, DIE);
			return (YES);
		}
		philo = philo->next;
		pthread_mutex_unlock(&philo->param->common_access_mutex);
	}
	return (NO);
}

int	ft_checkenougheat(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->param->common_access_mutex);
	res = (philo->param->need_to_eat_count == 0);
	pthread_mutex_unlock(&philo->param->common_access_mutex);
	return (res);
}

int	ft_game_is_on(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->param->common_access_mutex);
	if (philo->param->death == -1 && philo->param->need_to_eat_count != 0)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&philo->param->common_access_mutex);
	return (res);
}

int	ft_msgerr(char *error)
{
	printf("%s\n", error);
	return (1);
}
