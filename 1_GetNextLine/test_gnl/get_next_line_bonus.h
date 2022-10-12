/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 06:40:30 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 20:51:20 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	int				fd;
	char			*stock;
	int				stock_size;
	struct s_list	*next;
}	t_list;

enum
{
	CREATE_ONE,
	FREE_ONE,
	FREE_ALL
};

enum
{
	STR_MALLOC,
	LIST_MALLOC
};

enum
{
	JOIN,
	LENGTH
};

char	*get_next_line(int fd);
t_list	**ft_retrieve_el(int fd);
t_list	*ft_edit_list(t_list **ref_el, int action);
char	*ft_analyze_stock(t_list **cur_el, char **stock, int fd);
char	*ft_update_stock(char **stock, int stock_size, int index_nl);
void	*ft_mem_alloc(int n, int type_malloc);
int		ft_strjoin(char **s1, char **s2, int type_join, int addition);
char	*ft_substr(char **s, int start, int len);
int		ft_read_buffer(int fd, char **stock);
int		ft_index_nl(char *str);

#endif
