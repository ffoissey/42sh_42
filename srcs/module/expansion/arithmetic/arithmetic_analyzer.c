/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:13:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		m_error_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_ERROR;
	ft_dprintf(2, "42sh: %s : error token near %s\n"
			, arithmetic->input->buffer
			, g_shell->grammar_m[arithmetic->curr_token->type]);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
}

void		m_end_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_END;
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
}

char		*solve_expression(t_arithmetic *arithmetic)
{
	char		*output;
	t_infix		infix;

	output = NULL;
	ft_bzero(&infix, sizeof(t_infix));
	if (ft_stcksize(&arithmetic->processing) > 0)
		;
	else
		infix.type = 0;
	infix.calcul.size = ft_lstlen(arithmetic->solving);
	infix.calcul.head = arithmetic->solving;
	arithmetic->solving = NULL;
	if (calculator(&infix) == FAILURE)
		return (NULL);
	ft_asprintf(&output, "%lld", infix.result);
	return (output);
}

int8_t		arithmetic_analyzer(t_arithmetic *arithmetic)
{
	static t_ar_analyzer	*func = NULL;

	if (*func == NULL)
		func = init_math_analyzer();
	m_get_token(arithmetic, NULL);
	while (arithmetic->state != MATH_END && arithmetic->state != MATH_ERROR)
		(*func)[arithmetic->state][arithmetic->curr_token->type](arithmetic);
	if (arithmetic->state == MATH_END)
	{
		arithmetic->expanded = solve_expression(arithmetic);
		return (arithmetic->expanded == NULL ? FAILURE : SUCCESS);
	}
	return (FAILURE);
}
