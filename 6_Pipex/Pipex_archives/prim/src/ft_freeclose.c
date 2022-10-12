/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeclose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:17:04 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 02:52:51 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freefd(int **fd, int end)
{
	int	i;

	i = -1;
	while (++i != end && fd[i])
		free(fd[i]);
	if (fd)
		free(fd);
}

int	ft_closechildfd(t_data *ppx, int fdi)
{
	int	i;

	i = -1;
	while (ppx->fd[++i])
	{
		if (i != fdi - 1)
			close (ppx->fd[i][0]);
		if (i != fdi)
			close (ppx->fd[i][1]);
	}
	return (0);
}

void	ft_closeallfd(t_data *ppx)
{
	int	i;

	i = -1;
	while (ppx->fd[++i])
	{
		close(ppx->fd[i][0]);
		close(ppx->fd[i][1]);
	}
	close(ppx->fd_infile);
	close(ppx->fd_outfile);
}

void	ft_freeclose(t_data *ppx)
{
	ft_closeallfd(ppx);
	ft_freefd(ppx->fd, -1);
	if (ppx->pid)
		free(ppx->pid);
}
