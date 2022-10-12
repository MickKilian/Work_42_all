/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:41:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/09 01:57:53 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_parsing(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 5)
		return(ft_parserror(TOOFEW));
	else
	{
		while (++i < argc)
		{
			ft_printf("i = %d\n", i);
			ft_printf("argc = %d\n", argc);
			ft_readcmd(i, argc, argv);
		}
	}
	return (0);
}

int	ft_parserror(int id)
{
	if (id == TOOFEW)
	{
		ft_printf("Please enter at least 2 commands and exactly 2 file names in this form : \n");
		ft_printf("./pipex file1 cmd1 cmd2 ... cmdn file2\n");
	}
	return (1);
}

int	ft_readcmd(int i, int argc, char *argv[])
{
	int		j;
	char	**cmd;
	int		id;
	int		fd[2];
	int		file_id;

	ft_printf("Now in readcmd\n");
	if (pipe(fd) == -1)
	{
		ft_printf("Error when creating the pipe.\n");
		return (2);
	}
	id = fork();
	if (id == -1)
	{
		ft_printf("Error with the fork.\n");
		return (1);
	}
	if (id == 0)
	{
		ft_printf("Just forked\n");
		ft_printf("We are in the Child process.\n");
		ft_printf("We will read and execute the command.\n");
		if (i == 1)
		{
			ft_printf("Dealing with infile.\n");
			ft_managefile(argv[1], &file_id, STDIN_FILENO);
		}
		else if (i == argc)
		{
			ft_printf("Dealing with outfile.\n");
			ft_managefile(argv[argc - 1], &file_id, STDOUT_FILENO);
		}
		else
		{
			ft_redirect(STDOUT_FILENO, fd[0]);
			ft_redirect(STDIN_FILENO, fd[1]);
		}
		j = 0;
		cmd = ft_split(argv[i], ' ');
		while (cmd[j++])
		{
			ft_printf("cmd[%d] = %s\n", j - 1, cmd[j - 1]);
		}
		if (cmd[0])
		{
			ft_printf("Il existe au moins un mot dans la commande, elle va etre executee.\n");
			ft_execve(cmd);
		}
		else
			ft_printf("La commande est vide.\n");
	}
	else
	{
		ft_printf("We are in the Parent process.\n");
		wait(NULL);
	}
	return (0);
}
