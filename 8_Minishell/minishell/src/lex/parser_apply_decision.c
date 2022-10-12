/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_apply_decision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/26 02:25:44 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_apply_decision(t_lex *lex)
{
//	printf("\nlex->prev_decision\n");
//	ft_print_lex_proc(lex->prev_decision);
	lex->new_decision = lex->decision[lex->prev_decision.read_mode][ft_char_type(lex->user_input[0])];
	//printf("char : %d\n", lex->user_input[0]);
	//printf("char type : %d\n", ft_char_type(lex->user_input[0]));
	//printf("\nlex->new_decision\n");
	//ft_print_lex_proc(lex->new_decision);
	lex->ft[lex->new_decision.buffer_action](lex);
	lex->ft[lex->new_decision.char_action](lex);
	//lex->read_mode = lex->new_decision.read_mode;
	lex->prev_decision = lex->new_decision;
	//ft_print_lex_proc(lex->new_decision);
	return (0);
}

int	ft_print_lex_proc(t_lex_proc proc)
{
	printf("buffer_action : %d\n", proc.buffer_action);
	printf("character_action : %d\n", proc.char_action);
	printf("read_mode : %d\n", proc.read_mode);
	printf("token_type : %d\n", proc.token_type);
	return (0);
}
