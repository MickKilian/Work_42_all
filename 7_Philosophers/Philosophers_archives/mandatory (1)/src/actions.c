/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:57:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/01 05:56:43 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_action(t_philo *philo, int action)
{
	return ((philo->param->ft_action[action])(philo));
}

int	ft_take2forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->fork[philo->order_forks[0]].mutex);
	ft_takefork(philo);
	pthread_mutex_lock(&philo->param->fork[philo->order_forks[1]].mutex);
	ft_takefork(philo);
	return (0);
}

int	ft_takefork(t_philo *philo)
{
	ft_changestate(philo, FORK);
	return (0);
}

int	ft_letfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->param->fork[philo->id - 1].mutex);
	pthread_mutex_unlock(&philo->param->fork[(philo->next->id - 1)].mutex);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	int	time;

	time = ft_gettime(philo->param->start);
	ft_last_eat_ex_ch(philo, time);
	if (ft_changestate(philo, EAT))
		return (1);
	ft_nb_eats_ex_ch(philo, ft_nb_eats_ex(philo) + 1);
	if (ft_myusleep(philo, philo->param->tm_eat))
	{
		ft_letfork(philo);
		return (1);
	}
	ft_letfork(philo);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_changestate(philo, SLEEP);
	if (ft_myusleep(philo, philo->param->tm_sleep))
		return (1);
	return (0);
}

int	ft_think(t_philo *philo)
{
	ft_changestate(philo, THINK);
	if (ft_myusleep(philo, philo->param->tm_think))
		return (1);
	return (0);
}

int	ft_die(t_philo *philo)
{
	ft_changestate(philo, DIE);
	return (1);
}

int	ft_changestate(t_philo *philo, int status)
{
	ft_status_ex_ch(philo, status);
	if ((ft_dead_ex(philo) == -1 && !ft_enough_eat_ex(philo)) || ft_status_ex(philo) == DIE)
		ft_displaystate(philo, ft_gettime(philo->param->start));
	return (0);
}
