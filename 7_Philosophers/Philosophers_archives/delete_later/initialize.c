/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:45:27 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 00:15:27 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_param(t_data *param, int argc, char **argv)
{
	int	i;

	i = 0;
	param->nb_philos = ft_atoi(argv[1]);
	param->tm_die = ft_atoi(argv[2]) * 1000;
	param->tm_eat = ft_atoi(argv[3]) * 1000;
	param->tm_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		param->min_eats = ft_atoi(argv[5]);
	param->need_to_eat_count = param->nb_philos;
	param->death = -1;
	pthread_mutex_init(&(param->common_access_mutex), NULL);
	param->txt_status[0] = "has taken a fork";
	param->txt_status[1] = "is eating";
	param->txt_status[2] = "is sleeping";
	param->txt_status[3] = "is thinking";
	param->txt_status[4] = "died";
	param->fork_mutex = (pthread_mutex_t *)ft_mem_alloc((param->nb_philos) * sizeof(pthread_mutex_t));
	while (i < param->nb_philos)
	{
		pthread_mutex_init(&(param->fork_mutex[i]), NULL);
		i++;
	}
	return (0);
}

t_philo	*ft_init_philo(t_data *param)
{
	int		i;
	int		j;
	t_philo	*philo;

	i = 1;
	philo = ft_new_philo(NULL, param, 1);
	while (i++ < param->nb_philos)
	{
		j = i - 1;
		philo->order[0] = (j - (j % 2)) % param->nb_philos;
		philo->order[1] = (j + (j % 2 - 1)) % param->nb_philos;
		philo->next = ft_new_philo(philo, param, i);
		philo = philo->next;
	}
	j++;
	philo->order[0] = (j - (j % 2)) % param->nb_philos;
	philo->order[1] = (j + (j % 2 - 1)) % param->nb_philos;
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
	//pthread_mutex_init(&(new_philo->fork_mutex), NULL);
	new_philo->param = param;
	new_philo->last_eat = 0;
	new_philo->nb_eats = 0;
	if (i == 1)
		new_philo->next = new_philo;
	else
		new_philo->next = philo->next;
	return (new_philo);
}
