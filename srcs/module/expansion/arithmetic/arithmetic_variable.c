/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:20:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		convert_operator(t_arithmetic *arithmetic, t_rpn_tk *token)
{
	if (arithmetic->curr_token->type == E_M_PLUS)
		token->value.type |= PLUS;
	else if (arithmetic->curr_token->type == E_M_MINUS)
		token->value.type |= MINUS;
	else if (arithmetic->curr_token->type == E_M_TIMES)
		token->value.type |= TIMES;
	else if (arithmetic->curr_token->type == E_M_DIVIDE)
		token->value.type |= DIVIDE;
	else if (arithmetic->curr_token->type == E_M_MODULO)
		token->value.type |= MODULO;
}

void		m_operator_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_OPERATOR;
	token.type = RPN_OPERATOR;
	convert_operator(arithmetic, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_parenthesis_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	if (arithmetic->curr_token->type == E_M_OPENP)
	{
		arithmetic->state = MATH_OPEN_PARENT;
		arithmetic->parenthesis++;
		token.type = RPN_PARENT_OPEN;
		token.value.type = OPEN_P;
	}
	else
	{
		arithmetic->state = MATH_CLOSE_PARENT;
		arithmetic->parenthesis--;
		token.type = RPN_PARENT_CLOSE;
		token.value.type = CLOSE_P;
	}
	if (arithmetic->parenthesis < 0)
		return (m_error_analyzer(arithmetic));
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_variable_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_VARIABLE;
	ft_stckpushnode(&arithmetic->processing, arithmetic->current);
	m_get_token(arithmetic, NULL);
}

void		m_flush_variable_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;
	int			index;

	arithmetic->state = MATH_VARIABLE_FLUSH;
	ft_bzero(&token, sizeof(t_rpn_tk));
	index = 0;
	node = ft_stckpopnode(&arithmetic->processing);
	current = node->data;
	token.type = RPN_NUMBER;
	index = current->data[0] == '$' ? 1 : 0;
	if ((data = get_var(g_shell->intern, current->data + index)))
		token.value.digit = ft_atoll_base(data, DEC_BASE);
	else
		token.value.digit = 0;
	ft_lstdelone(&node, del_token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
}
