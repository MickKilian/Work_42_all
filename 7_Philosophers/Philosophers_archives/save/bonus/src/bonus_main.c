/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:12:42 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 05:58:50 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	main(int argc, char **argv)
{
	t_data	param;
	t_philo	*philo;

	if (ft_parsing(argc, argv))
		return (1);
	ft_bzero(&param, sizeof(t_data));
	ft_init_param(&param, argc, argv);
	philo = ft_init_philo(&param);
	ft_init_sem(&param);
	sem_post(param.stop_sem);
	sem_wait(param.stop_sem);
	if (param.nb_philos == 1)
		return (ft_case1philo(philo));
	ft_makechildrenproc(philo);
	sem_wait(param.stop_sem);
	//ft_endthreads(philo);
	ft_kill_proc(philo);
	ft_free_philo(philo);
	ft_close_sem(&param);
	return (0);
}

int	ft_case1philo(t_philo *philo)
{
	struct timeval	tick;

	gettimeofday(&tick, NULL);
	philo->param->start = ft_us(tick);
	ft_changestatus(philo, FORK);
	pthread_create(&philo->thread, NULL, ft_monitoring_death, (void *)philo);
	sem_wait(philo->param->stop_sem);
	ft_endthreads(philo);
	ft_free_philo(philo);
	return (0);
}

int	ft_makechildrenproc(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo->param->nb_philos)
	{
		philo->param->start = ft_gettime(0);
		philo->pid = fork();
		if (philo->pid == -1)
			return (1);
		if (philo->pid == 0)
		{
			ft_philolife(philo);
			exit (0);
		}
		philo = philo->next;
	}
	ft_myusleep(philo, philo->tm_die / 2);
	if (philo->param->min_eats > 0)
	{
		pthread_create(&philo->param->thread,
			NULL, ft_monitoring_eats, (void *)philo);
	}
	return (0);
}

void	ft_philolife(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_myusleep(philo, EVENPHILO_OFFSET);
	pthread_create(&philo->thread, NULL, ft_monitoring_death, (void *)philo);
	while (1)
	{
		if (ft_take2forks(philo) || ft_eat(philo)
			|| ft_sleep(philo) || ft_think(philo))
			break ;
	}
}
