/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:01:04 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 00:16:11 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take2forks(t_philo *philo)
{
	t_data	*param;

	param = philo->param;
	//printf("id : %d, left : %d, right : %d\n", philo->id, philo->order[0], philo->order[1]);
	pthread_mutex_lock(&param->fork_mutex[philo->order[0]]);
	//if (philo->param->nb_philos % 2)
	//	pthread_mutex_lock(&philo->fork_mutex);
	//else
	//	pthread_mutex_lock(&philo->next->fork_mutex);
	ft_changestatus(philo, FORK);
	if (!ft_game_is_on(philo))
		return (ft_letfork(philo));
	pthread_mutex_lock(&param->fork_mutex[philo->order[1]]);
	//if (philo->param->nb_philos % 2)
	//	pthread_mutex_lock(&philo->next->fork_mutex);
	//else
	//	pthread_mutex_lock(&philo->fork_mutex);
	ft_changestatus(philo, FORK);
	if (!ft_game_is_on(philo))
		return (ft_letfork(philo));
	return (0);
}

int	ft_letfork(t_philo *philo)
{
	t_data		*param;

	param = philo->param;
	pthread_mutex_unlock(&param->fork_mutex[philo->order[1]]);
	pthread_mutex_unlock(&param->fork_mutex[philo->order[0]]);
	//pthread_mutex_unlock(&philo->fork_mutex);
	//pthread_mutex_unlock(&philo->next->fork_mutex);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	int	res;

	if (ft_changestatus(philo, EAT))
		return (1);
	pthread_mutex_lock(&philo->param->common_access_mutex);
	philo->last_eat = ft_gettime(philo->param->start);
	pthread_mutex_unlock(&philo->param->common_access_mutex);
	res = ft_myusleep(philo, philo->param->tm_eat);
	ft_letfork(philo);
	if (res || ft_update_eat_count(philo))
		return (1);
	return (0);
}

int	ft_update_eat_count(t_philo *philo)
{
	int	res;

	res = 0;
	philo->nb_eats++;
	if (philo->nb_eats == philo->min_eats)
	{
		pthread_mutex_lock(&philo->param->common_access_mutex);
		if (--philo->param->need_to_eat_count == 0)
		{
			printf("%s\n", ENGH_EAT);
			res = 1;
		}
		pthread_mutex_unlock(&philo->param->common_access_mutex);
	}
	return (res);
}
