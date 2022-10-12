/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:22:22 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/08 16:08:52 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_new_command(t_token *token)
{
	t_command	*new;

	if (ft_mallocator(&new, sizeof(t_command)))
		return (0);
	//if (ft_mallocator(&new->id, sizeof(str)))
	//	return (0);
	//if (ft_mallocator(&new, sizeof(t_token)) || ft_mallocator(&new->id, sizeof(str)))
	//	return (0);
	new->token = ft_new_token(token->id);
	new->prev = new;
	new->next = new;
	//printf("ok\n");
	return (new);
}

t_command	*ft_command_addnext(t_command *current, t_command *next)
{
	if (!current)
		return (current = next, current);
	else if (!next)
		return(ft_msgerr(ERR_NULLCMD), NULL);
	else
	{
		next->prev = current;
		next->next = current->next;
		//if (current->next == current)
		//	current->prev = new;
		//else
		current->next->prev = next;
		current->next = next;
	}
	return (next);
}

t_command	*ft_command_jumpcurrent(t_command *prev, t_command *next)
{
	if (next->next != next)
	{
		prev->next = next;
		next->prev = prev;
	}
	return (next);
}

int	ft_free_commandlist(t_command *command)
{
	t_command	*temp;

	if (!command)
		return (1);
	while (1)
	{
		temp = command;
		command = ft_command_jumpcurrent(command->prev, command->next);
		ft_free_tokenlist(temp->token);
		free(temp);
		if (command == temp)
			break ;
		temp = NULL;
	}
	command = NULL;
	return (0);
}
