/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:31:35 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_m_start(t_ar_analyzer analyzer)
{
	analyzer[MATH_START][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_START][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_START][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_START][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_START][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_START][E_M_DPLUS] = m_preffix;
	analyzer[MATH_START][E_M_DMINUS] = m_preffix;
	analyzer[MATH_START][E_M_END] = m_end_analyzer;
}

void	init_m_open_parent(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPEN_PARENT][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_DPLUS] = m_preffix;
	analyzer[MATH_OPEN_PARENT][E_M_DMINUS] = m_preffix;
}

void	init_m_close_parent(t_ar_analyzer analyzer)
{
	analyzer[MATH_CLOSE_PARENT][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_LESS] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_AND] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_OR] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_END] = m_end_analyzer;
}

void	init_m_unary(t_ar_analyzer analyzer)
{
	analyzer[MATH_UNARY][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_UNARY][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_UNARY][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_UNARY][E_M_DPLUS] = m_preffix;
	analyzer[MATH_UNARY][E_M_DMINUS] = m_preffix;
	analyzer[MATH_UNARY][E_M_STRING] = m_variable_analyzer;
}

void	init_m_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_OPERATOR][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_OPERATOR][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_OPERATOR][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_OPERATOR][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_OPERATOR][E_M_DPLUS] = m_preffix;
	analyzer[MATH_OPERATOR][E_M_DMINUS] = m_preffix;
}
