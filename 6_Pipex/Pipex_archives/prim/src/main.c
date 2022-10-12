/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 05:20:04 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 03:15:55 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	ppx;

	ft_bzero(&ppx, sizeof(t_data));
	if (!ft_strncmp(argv[1], "here_doc", 9))
		ppx.hdoc = 1;
	else
		ppx.hdoc = 0;
	if (argc < 4 + ppx.hdoc)
		return (ft_printerr(ERR_ARGS));
	else
	{
		if (ft_initialize(&ppx, argc, argv, envp))
		{
			ft_printerr(ERR_INIT);
			//ft_freeclose(&ppx);
			return (1);
		}
		if (ft_pipex(&ppx, argv, envp))
		{
			free(ppx.pid);
			ft_freefd(ppx.fd, -1);
			//ft_freeclose(&ppx);
			return (1);
		}
		free(ppx.pid);
		ft_freefd(ppx.fd, -1);
		//ft_freeclose(&ppx);
	}
	return (0);
}
