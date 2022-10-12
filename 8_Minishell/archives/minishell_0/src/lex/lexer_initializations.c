/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initializations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/09/26 01:47:13 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ft_init_token_types(t_lex *lex)
{
	lex->token_types[NEW] = "new";
	lex->token_types[WORD] = "word";
	lex->token_types[ASSIGNMENT_WORD] = "assignement_word";
	lex->token_types[NAME] = "name";
	lex->token_types[NEW_LINE] = "new_line";
	lex->token_types[LSS] = "less";
	lex->token_types[GRT] = "greater";
	lex->token_types[GGRT] = "redir_append";
	lex->token_types[HEREDOC] = "heredoc";
	lex->token_types[PIPE] = "pipe";
	lex->token_types[OP_OR] = "or";
	lex->token_types[OP_AND] = "and";
	lex->token_types[IO_NUMBER] = "redirection";
	return (0);
}*/

const char	*ft_getlabel_token_types(const t_token_types index)
{
	static const char* type[LEN_TOKEN_TYPES] = {
		"new", "word",
		//"assignement_word", "name",
		"new_line", "simple_quote", "double_quote", "less", "greater", "redir_append",
		"heredoc", "pipe", "amp", "or", "and", "end_of_input"
	};
	return (type[index]);
}

int	ft_init_decisions(t_lex *lex)
{
	ft_init_decision_1(lex);
	ft_init_decision_2(lex);
	ft_init_decision_3(lex);
	ft_init_decision_4(lex);
	ft_init_decision_5(lex);
	ft_init_decision_6(lex);
	ft_init_decision_7(lex);
	lex->prev_decision = (t_lex_proc){KEEP, SKIP, NEW_MODE, NEW};
	return (0);
}
