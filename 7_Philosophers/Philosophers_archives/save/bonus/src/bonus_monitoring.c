/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:25:51 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 05:57:44 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void	*ft_monitoring_death(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		if (ft_checkdeath(philo))
		{
			sem_wait(philo->param->access_sem);
			break ;
		}
	}
	return (NULL);
}

void	*ft_monitoring_eats(void *philo_)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_;
	i = 0;
	while (i < philo->param->nb_philos)
	{
		sem_wait(philo->param->enough_sem);
		i++;
	}
	sem_post(philo->param->stop_sem);
	sem_wait(philo->param->access_sem);
	printf("%s\n", ENGH_EAT);
	return (NULL);
}

void	ft_endthreads(t_philo *philo)
{
	t_data	*param;

	param = philo->param;
	if (philo->param->min_eats > 0)
	{
		if (pthread_join(param->thread, NULL))
			return ;
	}
}

void	*ft_wait_children(void *philo_)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo_;
	while (i < philo->param->nb_philos)
	{
		waitpid(philo->pid, NULL, 0);
		i++;
	}
	exit (0);
}
