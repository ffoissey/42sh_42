/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:18:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		m_postincrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	current = ft_stckpop(&arithmetic->processing);
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE);
		data = ft_llitoa(token.value.digit + 1);
	}
	else
	{
		data = ft_strdup("1");
		token.value.digit = 0;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_strdel(&current->data);
	free(current);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
}

void		m_postdecrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	current = ft_stckpop(&arithmetic->processing);
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE);
		data = ft_llitoa(token.value.digit - 1);
	}
	else
	{
		data = ft_strdup("-1");
		token.value.digit = 0;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_strdel(&current->data);
	free(current);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
}

void		m_suffix(t_arithmetic *arithmetic)
{
	int			control;
	t_token		*token;

	token = ft_stcktop(&arithmetic->processing);
	arithmetic->state = MATH_SUFFIX;
	control = arithmetic->curr_token->type;
	m_get_token(arithmetic, &arithmetic->current);
	if (token->type == E_M_STRING)
	{
		if (control == E_M_DPLUS)
			m_postincrement_analyzer(arithmetic);
		else if (control == E_M_DMINUS)
			m_postdecrement_analyzer(arithmetic);
	}
	else
		m_error_analyzer(arithmetic);
}
