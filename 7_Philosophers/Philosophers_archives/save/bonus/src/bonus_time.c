/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 05:22:56 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/05 02:56:55 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

long	ft_gettime(long start)
{
	struct timeval	tick;

	gettimeofday(&tick, NULL);
	return (ft_elapsedtime(start, ft_us(tick)));
}

long	ft_us(struct timeval time)
{
	return (1e6 * time.tv_sec + time.tv_usec);
}

long	ft_elapsedtime(double start, double tick)
{
	return (tick - start);
}

int	ft_myusleep(t_philo *philo, long time)
{
	struct timeval	tick;
	long			start_time;

	gettimeofday(&tick, NULL);
	start_time = ft_us(tick);
	while (ft_gettime(start_time) < time)
	{
		if (ft_checkdeath(philo))
			return (1);
		else
			usleep(USLEEP_INC);
	}
	return (0);
}
