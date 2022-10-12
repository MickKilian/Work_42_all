/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:03:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/16 15:03:25 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_countwords(char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str && *str == ' ')
		str++;
	while (*str)
	{
		if (*str != ' ' && trigger == 0)
		{
			i++;
			trigger = 1;
		}
		if (*str == ' ')
			trigger = 0;
		str++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	while (str[i])
		i++;
	return (i);
}

void	ft_freemalloc(char **temp, int i)
{
	while (i--)
		free(temp[i]);
	free(temp);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = '\0';
		n--;
		s++;
	}
}

char	*ft_strndup(char *str, int n)
{
	char	*temp;
	int		i;

	temp = malloc((n + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_bzero(temp, (n + 1) * sizeof(char));
	i = 0;
	while (i < n)
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	ft_writeword(char *word)
{
	while (*word)
	{
		write(1, word, 1);
		word++;
	}
}

char	**ft_split(char *str)
{
	char	**temp;
	int		nb_words;
	int		i;
	int		count;

	nb_words = ft_countwords(str);
	temp = malloc((nb_words + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	ft_bzero(temp, (nb_words + 1) * sizeof(char *));
	//temp[nb_words] = NULL;
	i = 0;
	while (i < nb_words)
	{
		while (*str && *str == ' ')
			str++;
		count = 0;
		while (*str && *str != ' ')
		{
			count++;
			str++;
		}
		temp[i] = ft_strndup(str - count, count);
		if (!temp[i])
		{
			ft_freemalloc(temp, i);
			return (NULL);
		}
		i++;
	}
	return (temp);
}

void	rostring(int argc, char **argv)
{
	char	**temp;
	int		nb_words;
	int		i;

	if (argc > 1)
	{
		temp = ft_split(argv[1]);
		nb_words = ft_countwords(argv[1]);
		i = 1;
		while (i < nb_words)
		{
			ft_writeword(temp[i]);
			i++;
			if (i < nb_words || nb_words > 1)
				write (1, " ", 1);
		}
		ft_writeword(temp[0]);
	}
	write (1, "\n", 1);
	if (temp)
		ft_freemalloc(temp, nb_words);
}

int	main(int argc, char **argv)
{
	rostring(argc, argv);
	return (0);
}
