/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:45:27 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 04:59:21 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	ft_init_sem(t_data *param)
{
	sem_unlink("/forks");
	sem_unlink("/access");
	sem_unlink("/stop");
	sem_unlink("/enough");
	param->forks_sem = sem_open("forks", O_CREAT, 0600, param->nb_philos);
	param->access_sem = sem_open("access", O_CREAT, 0600, 1);
	param->stop_sem = sem_open("stop", O_CREAT, 0600, 0);
	param->enough_sem = sem_open("enough", O_CREAT, 0600, 0);
	return (0);
}

int	ft_init_param(t_data *param, int argc, char **argv)
{
	param->nb_philos = ft_atoi(argv[1]);
	param->tm_die = ft_atoi(argv[2]) * 1000;
	param->tm_eat = ft_atoi(argv[3]) * 1000;
	param->tm_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		param->min_eats = ft_atoi(argv[5]);
	param->txt_status[0] = "has taken a fork";
	param->txt_status[1] = "is eating";
	param->txt_status[2] = "is sleeping";
	param->txt_status[3] = "is thinking";
	param->txt_status[4] = "died";
	return (0);
}

t_philo	*ft_init_philo(t_data *param)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = ft_new_philo(NULL, param, 1);
	while (i++ < param->nb_philos)
	{
		philo->next = ft_new_philo(philo, param, i);
		philo = philo->next;
	}
	philo = philo->next;
	return (philo);
}

t_philo	*ft_new_philo(t_philo *philo, t_data *param, int i)
{
	t_philo	*new_philo;

	new_philo = (t_philo *)ft_mem_alloc(1 * sizeof(t_philo));
	new_philo->id = i;
	new_philo->status = THINK;
	new_philo->tm_die = param->tm_die;
	new_philo->tm_eat = param->tm_eat;
	new_philo->tm_sleep = param->tm_sleep;
	new_philo->min_eats = param->min_eats;
	new_philo->param = param;
	new_philo->last_eat = 0;
	new_philo->nb_eats = 0;
	if (i == 1)
		new_philo->next = new_philo;
	else
		new_philo->next = philo->next;
	return (new_philo);
}
