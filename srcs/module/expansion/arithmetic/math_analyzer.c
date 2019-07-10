/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:31:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		bzero_analyzer(t_ar_analyzer analyzer)
{
	int		index;
	int		state;

	index = 0;
	while (index < MATH_STATE)
	{
		state = 0;
		while (state < MATH_TOKEN)
			analyzer[index][state++] = m_error_analyzer;
		++index;
	}
}

void			init_m_preffix(t_ar_analyzer analyzer)
{
	analyzer[MATH_PREFFIX][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_LESS] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_AND] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_OR] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIX][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIX][E_M_END] = m_end_analyzer;
}

void			init_m_suffix(t_ar_analyzer analyzer)
{
	analyzer[MATH_SUFFIX][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_LESS] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_AND] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_OR] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_SUFFIX][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_SUFFIX][E_M_END] = m_end_analyzer;
}

void			init_m_logical_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_DPLUS] = m_preffix;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_DMINUS] = m_preffix;
}

t_ar_analyzer	*init_math_analyzer(void)
{
	static	t_ar_analyzer analyzer;

	bzero_analyzer(analyzer);
	init_m_start(analyzer);
	init_m_number(analyzer);
	init_m_unary(analyzer);
	init_m_operator(analyzer);
	init_m_logical_operator(analyzer);
	init_m_preffix(analyzer);
	init_m_suffix(analyzer);
	init_m_open_parent(analyzer);
	init_m_close_parent(analyzer);
	init_m_start(analyzer);
	init_m_variable(analyzer);
	init_m_flush_variable(analyzer);
	return (&analyzer);
}
