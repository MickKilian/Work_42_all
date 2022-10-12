/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:38:39 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/01 02:54:07 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void	ft_testforks(t_philo *philo)
//{
//	printf("id : %d, fork_1 : %d, fork_2 : %d\n", philo->id, philo->order_forks[0], philo->order_forks[1]);
//}

int	ft_philo(int argc, char ** argv)
{
	t_data			param;
	t_philo			*philo;
	struct timeval	tick;
	//int	i;

	ft_bzero(&param, sizeof(t_data));
	ft_init_param(&param, argc, argv);
	philo = ft_init_philo(&param);
	gettimeofday(&tick, NULL);
	param.start = ft_us(tick);
	//i = 0;
	//while (++i <= param.nb_philos)
	//{
	//	ft_testforks(philo);
	//	philo = philo->next;
	//}
	//return (0);
	if (param.nb_philos == 1)
		return(ft_case1philo(philo));
	ft_startthreads(philo);
	ft_monitoring(philo);
	ft_endthreads(philo);
	if (param.enough_eat)
		ft_msg(ENGH_EAT);
	if (param.dead != -1)
		ft_msg(PHI_DEAD);
	ft_free_philo(philo);
	free(param.fork);
	return (0);
}

int	ft_case1philo(t_philo *philo)
{
	ft_changestate(philo, FORKS);
	ft_monitoring(philo);
	ft_msg(PHI_DEAD);
	ft_free_philo(philo);
	free(philo->param->fork);
	return (0);
}

void	*ft_philolife(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	if (philo->id % 2 == 0)
		ft_myusleep(philo, EVENPHILO_OFFSET);
	while (!ft_test_gameover(philo))
	{
		//printf("------game_over : %d\n", ft_test_gameover(philo));
		//printf("------id : %d, nb_forks : %d\n", philo->id, ft_nb_forks_ex(philo));
		ft_action(philo, FORKS);
		ft_action(philo, EAT);
		ft_action(philo, SLEEP);
		ft_action(philo, THINK);
	}
	return (NULL);
}

void	ft_startthreads(t_philo *philo)
{
	int		i;
	t_data	*param;

	i = 0;
	param = philo->param;
	while (i < param->nb_philos)
	{
		pthread_create(&philo->thread, NULL, ft_philolife, (void *)philo);
		philo = philo->next;
		i++;
	}
}

void	ft_endthreads(t_philo *philo)
{
	int		i;
	t_data	*param;

	i = 0;
	param = philo->param;
	while (i < param->nb_philos)
	{
		//printf("waiting philo-id : %d\n", philo->id);
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

int	ft_monitoring(t_philo *philo)
{
	while (1)
	{
		if (ft_checkenougheat(philo) || ft_checkdead(philo))
			return (1);
	}
	return (0);
}

int	ft_checkdead(t_philo *philo)
{
	long long	elapsed_time;
	int			i;

	i = 0;
	while (++i <= philo->param->nb_philos)
	{
		elapsed_time = ft_elapsedtime(ft_last_eat_ex(philo), ft_gettime(philo->param->start));
		if (ft_status_ex(philo) != EAT && elapsed_time >= philo->param->tm_die)
		{
			ft_dead_ex_ch(philo, philo->id);
			ft_changestate(philo, DIE);
			return (YES);
		}
		philo = philo->next;
	}
	return (NO);
}

int	ft_checkenougheat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->param->min_eats)
	{
		while (++i <= philo->param->nb_philos)
		{
			if (ft_nb_eats_ex(philo) < philo->param->min_eats)
				return (ft_enough_eat_ex_ch(philo, NO));
			philo = philo->next;
		}
		return (ft_enough_eat_ex_ch(philo, YES));
	}
	return (ft_enough_eat_ex_ch(philo, NO));
}
