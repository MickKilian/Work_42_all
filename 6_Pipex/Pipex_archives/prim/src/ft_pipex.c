/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 05:25:42 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 03:25:38 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_data *ppx, char **argv, char **envp)
{
	if (ft_makepipes(ppx))
		return (ft_printerr(ERR_PIPES));
	if (ft_inoutfileredirect(ppx))
		return (1);
	if (ft_makechildrenproc(ppx, argv, envp))
		return (ft_printerr(ERR_CHILDREN));
	return (0);
}

int	ft_makepipes(t_data *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->nb_pipes)
	{
		if (pipe(ppx->fd[i]) == -1)
			return (1);
		i++;
	}
	ppx->fd[i] = NULL;
	return (0);
}

int	ft_makechildrenproc(t_data *ppx, char **argv, char **envp)
{
	int		i;

	i = -1;
	while (++i < ppx->nb_proc)
	{
		ppx->pid[i] = fork();
		if (ppx->pid[i] == -1)
			return (1);
		if (ppx->pid[i] == 0)
		{
			if (ft_fdchildredirect(ppx, i))
				return (1);
			ft_closechildfd(ppx, i);
			if (ft_execve(ppx, argv[i + 2 + ppx->hdoc], envp))
				return (ft_printerr(ERR_EXEC));
		}
	}
	ft_closeallfd(ppx);
	i = -1;
	while (++i < ppx->nb_proc)
		waitpid(ppx->pid[i], NULL, 0);
	return (0);
}
