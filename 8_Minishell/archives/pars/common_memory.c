/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/10 20:51:39 by mbourgeo         ###   ########.fr       */
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

int	ft_tklist_freeall(t_lex *lex)
{
	if (lex->temp)
	{
		free(lex->temp);
		lex->temp = NULL;
	}
	ft_free_tokenlist(lex->token);
	*(&(lex->token)) = NULL;
	ft_bzero(lex, sizeof(t_lex));
	ft_init_lex_decisions(lex);
	ft_init_lex_actions(lex);
	return (0);
}

int	ft_execfree_freeall(t_pars *pars)
{
	ft_free_cmdlist(pars->cmd);
	ft_print_debug_hdoc_list(pars->hdoc_list);
	ft_free_hdoclist(pars->hdoc_list);
	//ft_unlink_allhdoc(pars->hdoc_tab);
	ft_free_hdoctab(pars->hdoc_tab);
	return (0);
}

int	ft_pars_freeall(t_pars *pars)
{
	ft_free_commandlist(pars->command);
	*(&(pars->command)) = NULL;
	ft_bzero(pars, sizeof(t_pars));
	ft_init_pars_decisions(pars);
	ft_init_pars_actions(pars);
	ft_init_exp_decisions(pars);
	ft_init_exp_actions(pars);
	return (0);
}
