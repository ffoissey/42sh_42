/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_preffix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:05:49 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		m_preincrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	current = arithmetic->curr_token;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE) + 1;
		data = ft_llitoa(token.value.digit);
	}
	else
	{
		data = ft_strdup("1");
		token.value.digit = 1;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&arithmetic->current, del_token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_predecrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	current = arithmetic->curr_token;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE) - 1;
		data = ft_llitoa(token.value.digit);
	}
	else
	{
		data = ft_strdup("-1");
		token.value.digit = -1;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&arithmetic->current, del_token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_preffix(t_arithmetic *arithmetic)
{
	int			control;

	arithmetic->state = MATH_PREFFIX;
	control = arithmetic->curr_token->type;
	m_get_token(arithmetic, &arithmetic->current);
	if (arithmetic->curr_token->type == E_M_STRING)
	{
		if (control == E_M_DPLUS)
			m_preincrement_analyzer(arithmetic);
		else if (control == E_M_DMINUS)
			m_predecrement_analyzer(arithmetic);
		else
			m_error_analyzer(arithmetic);
	}
	else
		m_error_analyzer(arithmetic);
}
