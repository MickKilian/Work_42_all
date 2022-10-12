/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:57:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/01 03:23:43 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_action(t_philo *philo, int action)
{
	return ((philo->param->ft_action[action])(philo));
}

int	ft_forks(t_philo *philo)
{
	//printf("xxxxxxxid : %d, nb_forks : %d\n", philo->id, ft_nb_forks_ex(philo));
	//printf("xxxxxxxgame_over : %d\n", ft_test_gameover(philo));
	while (!ft_test_gameover(philo))
	{
		if(ft_nb_forks_ex(philo) < philo->param->nb_forks_max)
		{	
			if (philo->id == 3)
			{
				//printf("ooooooooid : %d, fork_1 : %d\n", philo->id, philo->order_forks[0]);
				//printf("ooooooooid : %d, fork_2 : %d\n", philo->id, philo->order_forks[1]);
			}
			if (!ft_fork_used_ex_ch(philo, philo->order_forks[ft_nb_forks_ex(philo)], YES))
			{
				//printf("id : %d, nb_forks : %d\n", philo->id, ft_nb_forks_ex(philo));
				ft_changestate(philo, FORKS);
			}
		}
		else
			return (0);
	}
	//printf("philo[%d] leaving thread\n", philo->id);
	return (1);
}

int	ft_letfork(t_philo *philo)
{

	ft_fork_used_ex_ch(philo, philo->order_forks[1], NO);
	ft_fork_used_ex_ch(philo, philo->order_forks[0], NO);
	ft_nb_forks_ex_ch(philo, 0);
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
	//if ((ft_dead_ex(philo) == -1 && !ft_enough_eat_ex(philo)) || ft_status_ex(philo) == DIE)
		ft_displaystatus(philo, ft_gettime(philo->param->start));
	return (0);
}

int	ft_test_gameover(t_philo *philo)
{
	return ((ft_dead_ex(philo) != -1) || ft_enough_eat_ex(philo));
}
