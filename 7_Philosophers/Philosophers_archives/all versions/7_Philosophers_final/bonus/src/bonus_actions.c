/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:57:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/07 03:46:46 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	ft_sleep(t_philo *philo)
{
	ft_changestatus(philo, SLEEP);
	if (ft_myusleep(philo, philo->param->tm_sleep))
		return (1);
	return (0);
}

int	ft_think(t_philo *philo)
{
	ft_changestatus(philo, THINK);
	if (ft_myusleep(philo, EVENPHILO_OFFSET))
		return (1);
	return (0);
}

int	ft_changestatus(t_philo *philo, int status)
{
	if (status == DIE)
	{
		printf("%ld %d %s\n", ft_gettime(philo->param->start) / 1000,
			philo->id, philo->param->txt_status[philo->status]);
	}
	sem_wait(philo->param->access_sem);
	philo->status = status;
	printf("%ld %d %s\n", ft_gettime(philo->param->start) / 1000,
		philo->id, philo->param->txt_status[philo->status]);
	sem_post(philo->param->access_sem);
	return (0);
}

int	ft_checkdeath(t_philo *philo)
{
	long	elapsed_time;

	sem_wait(philo->param->access_sem);
	elapsed_time = ft_elapsedtime(philo->last_eat,
			ft_gettime(philo->param->start));
	if (philo->status != EAT && elapsed_time >= philo->param->tm_die)
	{
		sem_post(philo->param->access_sem);
		sem_post(philo->param->stop_sem);
		ft_changestatus(philo, DIE);
		return (YES);
	}
	sem_post(philo->param->access_sem);
	return (NO);
}

int	ft_errmsg(char *str)
{
	printf("%s\n", str);
	return (1);
}
