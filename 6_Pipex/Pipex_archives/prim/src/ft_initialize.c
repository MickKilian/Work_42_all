/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:35:18 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 03:05:00 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_initialize(t_data *ppx, int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	ppx->path_env = ft_findpathstr(envp);
	if (!ppx->path_env)
		return (ft_printerr(ERR_PATHENV));
	ppx->nb_proc = argc - 3 - ppx->hdoc;
	ppx->nb_pipes = ppx->nb_proc - 1;
	ppx->pid = malloc((ppx->nb_proc) * sizeof(int));
	if (!ppx->pid)
		return (ft_printerr(ERR_MPROC));
	ppx->fd = malloc((ppx->nb_pipes + 1) * sizeof(int *));
	if (!ppx->fd)
	{
		free(ppx->pid);
		return (ft_printerr(ERR_MPIPE));
	}
	while (++i < ppx->nb_pipes)
	{
		ppx->fd[i] = malloc(2 * sizeof(int));
		if (!ppx->fd[i])
		{
			free(ppx->pid);
			ft_freefd(ppx->fd, i);
			return (ft_printerr(ERR_MPIPE));
		}
	}
	ppx->fd[i] = NULL;
	if (ft_openinfile(ppx, argv[1 + ppx->hdoc])
		|| ft_openoutfile(ppx, argv[argc - 1]))
		return (1);
	return (0);
}

int	ft_openinfile(t_data *ppx, char *str)
{
	if (ppx->hdoc)
	{
		ft_heredoc(ppx, str);
		ppx->fd_infile = open("heredoc_file", O_RDWR);
	}
	else
	{
		ppx->fd_infile = open(str, O_RDWR);
	}
	if (ppx->fd_infile < 0)
	{
		perror(str);
		return (1);
	}
	return (0);
}

int	ft_openoutfile(t_data *ppx, char *file)
{
	if (ppx->hdoc)
		ppx->fd_outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		ppx->fd_outfile = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (ppx->fd_outfile < 0)
	{
		ft_printerr(ERR_FILE);
		perror(file);
		return (1);
	}
	return (0);
}
