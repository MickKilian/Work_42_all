/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 04:55:10 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/30 09:50:38 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_isin(int c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (0);
		str++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (str1[i])
	{
		temp[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		temp[i + j] = str2[j];
		j++;
	}
	temp[i + j] = '\0';
	free(str1);
	return (temp);
}

char	*ft_read(int fd, char *temp)
{
	char	*buffer;
	int		bread;
	int		BUFFERSIZE;

	BUFFERSIZE = 10;
	bread = 1;
	buffer = malloc((BUFFERSIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (bread && ft_isin('\n', temp))
	{
		bread = read(fd, buffer, BUFFERSIZE);
		if (bread < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bread] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char	*ft_getline(char *temp)
{
	int		i;
	char	*line;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] && temp[i] == '\n')
		i++;
	line = malloc ((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] && temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
char	* ft_next(char *temp, char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!temp[0])
	{
		free(temp);
		return(NULL);
	}
	res = malloc((ft_strlen(temp) - ft_strlen(line) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = ft_strlen(line);
	while (temp[i + j])
	{
		res[j] = temp[j + i];
		j++;
	}
	res[j] = '\0';
	free(temp);
	return (res);
}

char	*ft_getnextline(int fd)
{
	static char	*temp;
	char	*line;

	if (!temp)
	{
		temp = malloc(sizeof(char));
		if (!temp)
			return (NULL);
		temp[0] = '\0';
	}
	temp = ft_read(fd, temp);
	line = ft_getline(temp);
	temp = ft_next(temp, line);
	return (line);
}
