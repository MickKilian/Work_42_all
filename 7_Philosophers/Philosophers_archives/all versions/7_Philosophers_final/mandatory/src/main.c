/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:12:42 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/07 01:24:07 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	param;
	t_philo	*philo;

	if (ft_parsing(argc, argv))
		return (1);
	ft_bzero(&param, sizeof(t_data));
	ft_init_param(&param, argc, argv);
	philo = ft_init_philo(&param);
	if (philo)
	{
		if (param.nb_philos == 1)
			return (ft_case1philo(philo));
		if (!ft_startthreads(philo))
		{
			ft_monitoring(philo);
			ft_endthreads(philo);
		}
	}
	ft_mutex_destroy(philo);
	ft_free_philo(philo);
	return (0);
}

int	ft_case1philo(t_philo *philo)
{
	struct timeval	tick;

	gettimeofday(&tick, NULL);
	philo->param->start = ft_us(tick);
	ft_changestatus(philo, FORK);
	ft_monitoring(philo);
	ft_mutex_destroy(philo);
	ft_free_philo(philo);
	return (0);
}

void	*ft_philolife(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	pthread_mutex_lock(&philo->param->common_access_mutex);
	pthread_mutex_unlock(&philo->param->common_access_mutex);
	if (philo->id % 2 == 0)
		ft_myusleep(philo, EVENPHILO_OFFSET);
	while (ft_game_is_on(philo))
	{
		if (ft_take2forks(philo) || ft_eat(philo)
			|| ft_sleep(philo) || ft_think(philo))
			break ;
	}
	return (NULL);
}

int	ft_startthreads(t_philo *philo)
{
	int		i;
	t_data	*param;

	i = 0;
	pthread_mutex_lock(&philo->param->common_access_mutex);
	param = philo->param;
	while (i < param->nb_philos)
	{
		if (pthread_create(&philo->thread, NULL, ft_philolife, (void *)philo))
		{
			pthread_mutex_unlock(&philo->param->common_access_mutex);
			return (ft_msgerr(ERR_THREAD));
		}
		philo = philo->next;
		i++;
	}
	param->start = ft_gettime(0);
	pthread_mutex_unlock(&philo->param->common_access_mutex);
	return (0);
}

int	ft_endthreads(t_philo *philo)
{
	int		i;
	t_data	*param;

	i = 0;
	param = philo->param;
	while (i < param->nb_philos)
	{
		if (pthread_join(philo->thread, NULL))
			return (ft_msgerr(ERR_JOIN));
		philo = philo->next;
		i++;
	}
	return (0);
}
