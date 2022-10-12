/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:35:52 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 00:54:05 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_findpathstr(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*ft_findcmdpath(char *cmd, char *path_str)
{
	char	**path_spt;
	char	*cmd_str;
	char	*temp;

	path_spt = ft_split(path_str, ':');
	if (!path_spt)
		return (NULL);
	while (*path_spt)
	{
		temp = ft_strjoin(*path_spt, "/");
		cmd_str = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(cmd_str, 0))
			return (cmd_str);
		path_spt++;
	}
	return (NULL);
}

int	ft_execve(t_data *ppx, char *cmd_str, char **envp)
{
	char	**cmd_spt;

	cmd_spt = ft_split(cmd_str, ' ');
	if (!cmd_spt)
		return (ft_printerr(ERR_CMDSPLIT));
	else
	{
		ppx->cmd_path = ft_findcmdpath(cmd_spt[0], ppx->path_env);
		if (!ppx->cmd_path)
		{
			free(cmd_spt);
			return (ft_printerr(ERR_CMDPATH));
		}
		if (execve(ppx->cmd_path, cmd_spt, envp) == -1)
			return (ft_printerr(ERR_EXECVE));
	}
	return (0);
}
