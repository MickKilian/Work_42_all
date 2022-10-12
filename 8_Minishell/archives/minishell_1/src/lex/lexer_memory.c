/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/28 00:42:50 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = '\0';
}

int	ft_mallocator(void *ptr, size_t size)
{
	*(void **)ptr = malloc(size);
	if (!*(void **)ptr)
		return (ft_msgerr(ERR_MALLOC), 1);
	ft_bzero(*(void **)ptr, size);
	return (0);
}

int	ft_freeall(t_lex *lex)
{
	if (lex->temp)
	{
		free(lex->temp);
		lex->temp = NULL;
	}
	//ft_bzero(&lex->prev_decision, sizeof(t_lex_proc));
	//ft_bzero(&lex->new_decision, sizeof(t_lex_proc));
	//lex->nb_taken_char = 0;
	//lex->nb_of_tokens = 0;
	//printf("in freeall\n");
	//lex->prev_decision = NUL;
	//lex->new_decision = NUL;
	ft_free_tokenlist(lex);
	*(&(lex->token)) = NULL;
	ft_bzero(lex, sizeof(t_lex));
	ft_init_lex_decisions(lex);
	ft_init_lex_actions(lex);
	return (0);
}
