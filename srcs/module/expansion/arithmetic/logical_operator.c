/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:04:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		convert_logical_operator(t_arithmetic *arithmetic, t_rpn_tk *token)
{
	if (arithmetic->curr_token->type == E_M_LESS)
		token->value.type = LESS;
	else if (arithmetic->curr_token->type == E_M_GREAT)
		token->value.type = GREAT;
	else if (arithmetic->curr_token->type == E_M_LESSEQ)
		token->value.type = LESSEQ;
	else if (arithmetic->curr_token->type == E_M_GREATEQ)
		token->value.type = GREATEQ;
	else if (arithmetic->curr_token->type == E_M_EQUAL)
		token->value.type = EQUAL;
	else if (arithmetic->curr_token->type == E_M_NEQUAL)
		token->value.type = DIFF;
	else if (arithmetic->curr_token->type == E_M_AND)
		token->value.type = AND;
	else if (arithmetic->curr_token->type == E_M_OR)
		token->value.type = OR;
}

void		m_logical_operator(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_LOGICAL_OPERATOR;
	token.type = RPN_OPERATOR;
	convert_logical_operator(arithmetic, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}
