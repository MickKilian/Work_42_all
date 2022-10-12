/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_ascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/10 23:36:08 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_type(char c)
{
	if (c != NL && (c == SP || (c >= HTAB && c <= CRET)))
		 return(SEP_CHAR);
	if (c == QUOT)
		 return(DBL_CHAR);
	if (c == APOS)
		 return(SPL_CHAR);
	if (c == VERBAR)
		 return(PIPE_CHAR);
	//if (c == COMAND)
	//	 return(AMP_CHAR);
	if (c == LT)
		 return(LT_CHAR);
	if (c == GT)
		 return(GT_CHAR);
	if (c == NUL || c == NL)
		 return(END_CHAR);
	if (c == DOLLAR)
		 return(DOL_CHAR);
	if (c == ESCP)
		 return(ERR_CHAR);
	else
		 return(STD_CHAR);
}
