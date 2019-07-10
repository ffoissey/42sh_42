/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_base_states.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:40:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		convert_number(t_rpn_tk *current, t_token *token)
{
	size_t		control;

	if (token->type == E_M_NB_OCT)
	{
		control = ft_strspn(token->data, OCTAL_BASE);
		if (token->data[control] != '\0')
			return (FAILURE);
		else
			current->value.digit = ft_atoll_base(token->data, OCTAL_BASE);
	}
	else if (token->type == E_M_NB_HEX)
	{
		ft_strupper(token->data);
		current->value.digit = ft_atoll_base(token->data + 2, HEX_BASE);
	}
	else
		current->value.digit = ft_atoll_base(token->data, DEC_BASE);
	return (SUCCESS);
}

void		m_number_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_NUMBER;
	token.type = RPN_NUMBER;
	if (convert_number(&token, arithmetic->curr_token) == FAILURE)
	{
		m_error_analyzer(arithmetic);
		return ;
	}
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		set_unary(t_token *preffix, t_rpn_tk *token)
{
	if (preffix->type == E_M_PLUS)
		token->value.type |= UNARY_PLUS;
	else
		token->value.type |= UNARY_MINUS;
}

void		m_unary_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_UNARY;
	token.type = RPN_OPERATOR;
	set_unary(arithmetic->curr_token, &token);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}
