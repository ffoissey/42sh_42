/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:33:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_m_number(t_ar_analyzer analyzer)
{
	analyzer[MATH_NUMBER][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_LESS] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_AND] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_OR] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_END] = m_end_analyzer;
}

void	init_m_variable(t_ar_analyzer analyzer)
{
	analyzer[MATH_VARIABLE][E_M_PLUS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_MINUS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_TIMES] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_MODULO] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_DIVIDE] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_LESS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_GREAT] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_LESSEQ] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_GREATEQ] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_EQUAL] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_NEQUAL] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_AND] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_OR] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_DPLUS] = m_suffix;
	analyzer[MATH_VARIABLE][E_M_DMINUS] = m_suffix;
	analyzer[MATH_VARIABLE][E_M_END] = m_flush_variable_analyzer;
}

void	init_m_flush_variable(t_ar_analyzer analyzer)
{
	analyzer[MATH_VARIABLE_FLUSH][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_LESS] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_AND] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_OR] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_END] = m_end_analyzer;
}
