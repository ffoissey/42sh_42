/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:45:45 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		do_logical(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (OPERATOR & AND))
		first->value.digit = (first->value.digit && second->value.digit);
	else if (curr->value.type & (OPERATOR & OR))
		first->value.digit = (first->value.digit || second->value.digit);
}

void		do_compare(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (OPERATOR & LESS))
		first->value.digit = (first->value.digit < second->value.digit);
	else if (curr->value.type & (OPERATOR & LESSEQ))
		first->value.digit = (first->value.digit <= second->value.digit);
	else if (curr->value.type & (OPERATOR & GREAT))
		first->value.digit = (first->value.digit > second->value.digit);
	else if (curr->value.type & (OPERATOR & GREATEQ))
		first->value.digit = (first->value.digit >= second->value.digit);
	else if (curr->value.type & (OPERATOR & EQUAL))
		first->value.digit = (first->value.digit == second->value.digit);
	else if (curr->value.type & (OPERATOR & DIFF))
		first->value.digit = (first->value.digit != second->value.digit);
	else if (curr->value.type & (OPERATOR & EQUAL))
		first->value.digit = (first->value.digit == second->value.digit);
}

void		do_high_op(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (OPERATOR & TIMES))
		first->value.digit *= second->value.digit;
	else
	{
		if (second->value.digit == 0)
			ft_printf("Division by zero\n");
		else if (curr->value.type & (OPERATOR & DIVIDE))
			first->value.digit /= second->value.digit;
		else if (curr->value.type & (OPERATOR & MODULO))
			first->value.digit %= second->value.digit;
	}
}

void		do_low_op(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (OPERATOR & PLUS))
		first->value.digit += second->value.digit;
	else if (curr->value.type & (OPERATOR & MINUS))
		first->value.digit -= second->value.digit;
}

void		do_unary(t_rpn_tk *number, t_rpn_tk *curr)
{
	if (curr->value.type & (OPERATOR & UNARY_MINUS))
		number->value.digit = -1 * number->value.digit;
	else if (curr->value.type & (OPERATOR & UNARY_PLUS))
		number->value.digit = 1 * number->value.digit;
}
