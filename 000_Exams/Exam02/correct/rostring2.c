/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:23:45 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/19 23:56:19 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

int	main(int argc, char **argv)
{
	int i;
	int first;

	i = 0;
	if( argc > 1)
	{
		while (argv[1][i] && (argv[1][i] == ' ' || argv[1][i] == '\t'))
			i++;
		if (argv[1][i])
			first = i;
		while (argv[1][i] && (argv[1][i] != ' ' && argv[1][i] != '\t'))
			i++;
		while (argv[1][i] && (argv[1][i] == ' ' || argv[1][i] == '\t'))
			i++;
		while (argv[1][i])
		{
			while (argv[1][i] && (argv[1][i] != ' ' && argv[1][i] != '\t'))
			{
				write(1, &argv[1][i], 1);
				i++;
			}
			write(1, " ", 1);
			while (argv[1][i] && (argv[1][i] == ' ' || argv[1][i] == '\t'))
				i++;
		}
		i = first;
		while (argv[1][i] && (argv[1][i] != ' ' && argv[1][i] != '\t'))
		{
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
