/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:01:04 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 05:53:20 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	ft_take2forks(t_philo *philo)
{
	sem_wait(philo->param->forks_sem);
	ft_changestatus(philo, FORK);
	sem_wait(philo->param->forks_sem);
	ft_changestatus(philo, FORK);
	return (0);
}

int	ft_letfork(t_philo *philo)
{
	sem_post(philo->param->forks_sem);
	sem_post(philo->param->forks_sem);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	int	res;

	ft_changestatus(philo, EAT);
	sem_wait(philo->param->access_sem);
	philo->last_eat = ft_gettime(philo->param->start);
	sem_post(philo->param->access_sem);
	res = ft_myusleep(philo, philo->param->tm_eat);
	ft_letfork(philo);
	if (res || ft_update_eat_count(philo))
		return (1);
	return (0);
}

int	ft_update_eat_count(t_philo *philo)
{
	philo->nb_eats++;
	if (philo->nb_eats == philo->min_eats)
	{
		sem_wait(philo->param->access_sem);
		sem_post(philo->param->enough_sem);
		sem_post(philo->param->access_sem);
	}
	return (0);
}
