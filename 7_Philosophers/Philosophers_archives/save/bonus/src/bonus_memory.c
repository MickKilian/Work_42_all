/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 04:12:38 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 05:53:11 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

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

	i = 0;
	nb = philo->param->nb_philos;
	while (++i < nb)
	{
		temp = philo->next;
		free(philo);
		philo = NULL;
		philo = temp;
	}
	free(philo);
}

void	ft_close_sem(t_data *param)
{
	sem_unlink("/forks");
	sem_unlink("/access");
	sem_unlink("/stop");
	sem_unlink("/enough");
	sem_close(param->forks_sem);
	sem_close(param->access_sem);
	sem_close(param->stop_sem);
	sem_close(param->enough_sem);
}

int	ft_kill_proc(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->param->nb_philos)
	{
		usleep(500);
		kill(philo->pid, SIGKILL);
		philo = philo->next;
		i++;
	}
	return (0);
}
