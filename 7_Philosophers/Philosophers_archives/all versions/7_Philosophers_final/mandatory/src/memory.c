/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 04:12:38 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/07 01:19:26 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_mem_alloc(int n)
{
	char	*str;

	str = malloc((n) * sizeof(char));
	if (!str)
		return (NULL);
	ft_bzero(str, n);
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = '\0';
}

void	ft_free_philo(t_philo *philo)
{
	t_philo	*temp;
	int		nb;
	int		i;

	i = 1;
	nb = philo->param->nb_philos;
	while (i < nb)
	{
		temp = philo->next;
		if (philo)
			free(philo);
		philo = NULL;
		philo = temp;
		i++;
	}
	free(philo);
}

int	ft_mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->param->common_access_mutex);
	while (i < philo->param->nb_philos)
	{
		pthread_mutex_destroy(&philo->fork_mutex);
		philo = philo->next;
		i++;
	}
	return (0);
}
